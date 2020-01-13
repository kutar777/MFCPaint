using System.Collections;
using System.Collections.Generic;
using System.Linq;
using UnityEngine;
using UnityEngine.Audio;

namespace SoundSystem
{
    public class SoundManager : MonoBehaviour
    {
        public static SoundManager Instance{get; private set;}
        
        public List<AudioClip> menuSeAudioClipList = new List<AudioClip>();
        private AudioSource menuSeAudioSource;
        
        public List<AudioClip> environmentAudioClipList = new List<AudioClip>();
        private AudioSource environmentAudioSource;

        public List<AudioClip> voiceAudioClipList = new List<AudioClip>();
        private AudioSource voiceAudioSource;
        
        public List<AudioClip> bgmAudioClipList = new List<AudioClip>();
        private List<AudioSource> bgmAudioSourceList = new List<AudioSource>();
        private const int BGMAudiosourceNum = 2;

        private List<IEnumerator> fadeCoroutines = new List<IEnumerator>();

        [SerializeField, HeaderAttribute("Audio Mixer")]
        public AudioMixer audioMixer;
        public AudioMixerGroup bgmAMG, menuSeAMG, envAMG, voiceAMG;

        public AudioMixer effectAudioMixer;

        public bool IsPaused { get; private set; }

        private const string MasterVolumeParamName = "MasterVolume";
        private const string GameSeVolumeParamName = "GameSEVolume";
        private const string BGMVolumeParamName = "BGMVolume";
        private const string EnvVolumeParamName = "EnvironmentVolume";
        
        private void Awake()
        {
            if (Instance == null)
            {
                Instance = this;
                DontDestroyOnLoad(this);
            }
            else
            {
                Destroy(this);
                return;
            }
        
            menuSeAudioSource = InitializeAudioSource(this.gameObject, false, menuSeAMG);
            bgmAudioSourceList = InitializeAudioSources(this.gameObject, true, bgmAMG, BGMAudiosourceNum);
            environmentAudioSource = InitializeAudioSource(this.gameObject, true, envAMG);
            
            voiceAudioSource = InitializeAudioSource(this.gameObject, false, voiceAMG);
        
            IsPaused = false;
        }

        public float MasterVolume
        {
            get { return audioMixer.GetVolumeByLinear(MasterVolumeParamName); }
            set { audioMixer.SetVolumeByLinear(MasterVolumeParamName, value); }
        }
        
        public float GameSeVolume
        {
            get { return audioMixer.GetVolumeByLinear(GameSeVolumeParamName); }
            set { audioMixer.SetVolumeByLinear(GameSeVolumeParamName, value); }
        }
        
        public float BGMVolume
        {
            get { return audioMixer.GetVolumeByLinear(BGMVolumeParamName); }
            set { audioMixer.SetVolumeByLinear(BGMVolumeParamName, value); }
        }
        
        public float EnvironmentVolume
        {
            get { return audioMixer.GetVolumeByLinear(EnvVolumeParamName); }
            set { audioMixer.SetVolumeByLinear(EnvVolumeParamName, value); }
        }

        public void ChangeSnapshot(string snapshotName, float transitionTime = 1f)
        {
            AudioMixerSnapshot snapshot = effectAudioMixer.FindSnapshot(snapshotName);
        
            if (snapshot == null)
            {
                Debug.Log(snapshotName + "は見つかりません");
            }
            else
            {
                snapshot.TransitionTo(transitionTime);
            }
        }
        
        public void Pause()
        {
            IsPaused = true;

            fadeCoroutines.ForEach(StopCoroutine);
            
            environmentAudioSource.Pause();
            voiceAudioSource.Pause();
            bgmAudioSourceList.ForEach(bas => bas.Pause());
        }

        public void Resume()
        {
            IsPaused = false;

            fadeCoroutines.ForEach(routine =>StartCoroutine(routine));
            
            environmentAudioSource.UnPause();
            voiceAudioSource.UnPause();
            bgmAudioSourceList.ForEach(bas => bas.UnPause());          
        }

        private List<AudioSource> InitializeAudioSources(GameObject parentGameObject, bool isLoop = false,
            AudioMixerGroup amg = null, int count = 1)
        {
            List<AudioSource> audioSources = new List<AudioSource>();

            for (int i = 0; i < count; i++)
            {
                var audioSource = InitializeAudioSource(parentGameObject, isLoop, amg);
                audioSources.Add(audioSource);
            }

            return audioSources;
        }

        private AudioSource InitializeAudioSource(GameObject parentGameObject, bool isLoop = false, AudioMixerGroup amg = null)
        {
            var audioSource = parentGameObject.AddComponent<AudioSource>();
            
            audioSource.loop = isLoop;
            audioSource.playOnAwake = false;
        
            if (amg != null)
            {
                audioSource.outputAudioMixerGroup = amg;
            }
        
            return audioSource;
        }

        public void PlaySe(string clipName)
        {
            var audioClip = menuSeAudioClipList.FirstOrDefault(clip => clip.name == clipName);
            
            if (audioClip == null)
            {
                Debug.Log(clipName + "は見つかりません");
                return;
            }
            
            menuSeAudioSource.Play(audioClip);
        }
        
        public void PlayEnvironment(string clipName)
        {
            if (IsPaused) return;
            
            var audioClip = environmentAudioClipList.FirstOrDefault(clip => clip.name == clipName);
            
            if (audioClip == null)
            {
                Debug.Log(clipName + "は見つかりません");
                return;
            }
            
            StartCoroutine(environmentAudioSource.PlayRandomStart(audioClip));
        }

        public void StopEnvironment()
        {
            if (IsPaused) return;
            
            if (environmentAudioSource.isPlaying)
            {
                environmentAudioSource.Stop();
            }
        }

        public void PlayBGMWithFadeIn(string clipName, float fadeTime = 2f)
        {
            if (IsPaused) return;
            
            var audioClip = bgmAudioClipList.FirstOrDefault(clip => clip.name == clipName);
            
            if (audioClip == null)
            {
                Debug.Log(clipName + "は見つかりません");
                return;
            }
            
            if (bgmAudioSourceList.Any(source => source.clip == audioClip))
            {
                Debug.Log(clipName + "はすでに再生されています");
                return;
            }

            StopBGMWithFadeOut(fadeTime);//現在再生中のBGMをフェードアウトする//

            AudioSource audioSource = bgmAudioSourceList.FirstOrDefault(asb => asb.isPlaying == false);
            
            if (audioSource != null)
            {
                IEnumerator routine = audioSource.PlayWithFadeIn(audioClip, fadeTime);
                fadeCoroutines.Add(routine);
                StartCoroutine(routine);
            }
        }
        
        public void StopBGMWithFadeOut(string clipName, float fadeTime = 2f)
        {
            if (IsPaused) return;
            
            AudioSource audioSource = bgmAudioSourceList.FirstOrDefault(bas => bas.clip.name == clipName);

            if (audioSource == null || audioSource.isPlaying == false)
            {
                Debug.Log(clipName + "は再生されていません");
                return;
            }

            IEnumerator routine = audioSource.StopWithFadeOut(fadeTime);
            StartCoroutine(routine);
            fadeCoroutines.Add(routine);
        }

        public void StopBGMWithFadeOut(float fadeTime = 2f)
        {
            if (IsPaused) return;
            
            fadeCoroutines.ForEach(StopCoroutine);
            fadeCoroutines.Clear();

            fadeCoroutines = bgmAudioSourceList.Where(asb => asb.isPlaying)
            .ToList()
            .ConvertAll(asb =>
                {
                    IEnumerator routine = asb.StopWithFadeOut(fadeTime);
                    StartCoroutine(routine);
                    return routine;
                });
        }

        public void PlayVoice(string clipName, float delayTime = 0f)
        {
            var audioClip = voiceAudioClipList.FirstOrDefault(clip => clip.name == clipName);
            
            if (audioClip == null)
            {
                Debug.Log(clipName + "は見つかりません");
                return;
            }
            
            voiceAudioSource.clip = audioClip;
            voiceAudioSource.PlayDelayed(delayTime);
            
            voiceAudioSource.PlayScheduled (AudioSettings.dspTime + delayTime);
        }
        
    }

}
