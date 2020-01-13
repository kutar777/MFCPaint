using UnityEngine;
using System.Collections;
using System.Collections.Generic;
using SoundSystem;
using UnityEngine.Events;

namespace ForestryLife
{
    public class GameBaseMain : MonoBehaviour
    {
        [SerializeField]
        public PlayerCharacter playerCharacter;

        [SerializeField]
        public MainUI mainUI;

        public VolumeConfigUI volumeConfigUI;

        private bool isMovingStage = false;

        public bool IsPaused { get; private set; }


        private void Start()
        {
            StageParent stageParent = FindObjectOfType<StageParent>();

            if (stageParent == null)
            {
                mainUI.BlackOutScreen();

                SceneLoader.Instance.LoadAdditiveWithCallback("Stage_House", () => StartCoroutine(LoadFirstStageCoroutine()));
            }
            else
            {
                SceneLoader.Instance.ActiveLoadedScene("Stage_" + stageParent.GetStageName());
                Instantiate();
            }

            volumeConfigUI.SetMasterSliderEvent(vol => SoundManager.Instance.MasterVolume = vol);
            volumeConfigUI.SetBGMSliderEvent(vol => SoundManager.Instance.BGMVolume = vol);
            volumeConfigUI.SetGameSeSliderEvent(vol => SoundManager.Instance.GameSeVolume = vol);
            volumeConfigUI.SetEnvSliderEvent(vol => SoundManager.Instance.EnvironmentVolume = vol);
            
        }

        public void Instantiate(string startPointName = "")
        {
            StageParent stageParent = FindObjectOfType<StageParent>();

            if (stageParent == null)
            {
                Debug.LogError("Cant find stageparent");
            }
            else
            {
                SceneLoader.Instance.ActiveLoadedScene("Stage_" + stageParent.GetStageName());
                stageParent.Initialize(this);

                if (!string.IsNullOrEmpty(startPointName))
                {
                    Transform startPointTransform = stageParent.GetStartPointTransformByName(startPointName);
                    playerCharacter.Initialize(startPointTransform, stageParent.GetStageCamera());
                }
                else
                {
                    playerCharacter.Initialize(currentStageCamera: stageParent.GetStageCamera());
                }
            }

            mainUI.BlackInScreen(1f);
        }

        private IEnumerator LoadFirstStageCoroutine()
        {
            StageParent stageParent = FindObjectOfType<StageParent>();

            stageParent.Initialize(this);

            playerCharacter.Initialize(currentStageCamera: stageParent.GetStageCamera());
            
            SoundManager.Instance.ChangeSnapshot(stageParent.GetStageName());
            
            mainUI.BlackInScreen(1f);
            yield return new WaitForSeconds(1.2f);

            isMovingStage = false;

            mainUI.TapMoveButtonActive(true);
        }

        public void MoveStage(string fromStageName, string toStageName, string startPointName)
        {
            if (isMovingStage) return;//フェード処理中は移動しない//
        
            isMovingStage = true;
            mainUI.TapMoveButtonActive(false);
            
            SoundManager.Instance.ChangeSnapshot(toStageName);
        
            StartCoroutine(MoveStageCoroutine(fromStageName, toStageName, startPointName));
        }

        private IEnumerator MoveStageCoroutine(string fromStageName, string toStageName, string startPointName)
        {
            mainUI.BlackOutScreen(1f);
            yield return new WaitForSeconds(1.2f);

            //SoundManager.Instance.ClearAudioListenerPos();

            playerCharacter.Disable();

            SceneLoader.Instance.ReplaceSceneWithCallback("Stage_" + fromStageName, "Stage_" + toStageName, () => Instantiate(startPointName));

            mainUI.BlackInScreen(1f);
            yield return new WaitForSeconds(1.2f);

            isMovingStage = false;

            mainUI.TapMoveButtonActive(true);
        }

        public void PauseSwitch()
        {
            if (IsPaused) { Resume(); } else { Pause(); };
        }

        public void Pause()
        {
            IsPaused = true;
            playerCharacter.Pause();
        
            SoundManager.Instance.Pause();
        
            volumeConfigUI.Show();
            volumeConfigUI.SetMasterVolume(SoundManager.Instance.MasterVolume);
            volumeConfigUI.SetSeVolume(SoundManager.Instance.GameSeVolume);
            volumeConfigUI.SetBGMVolume(SoundManager.Instance.BGMVolume);
            volumeConfigUI.SetEnvVolume(SoundManager.Instance.EnvironmentVolume);    
        }

        public void Resume()
        {
            IsPaused = false;
            playerCharacter.Resume();

            SoundManager.Instance.Resume();

            volumeConfigUI.Hide();
        }

        public void PlayAxeAnimation(UnityAction cutCallback)
        {
            playerCharacter.Cut(cutCallback);
        }

        public void GameClear()
        {
            //SoundManager.Instance.PlayJingle("Clear");
            mainUI.ShowGameClear();
        }
    }
}