using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class PhotoMaker : MonoBehaviour {

    public List<Sprite> sprites;
    //public Image _image;
    public Transform canvasTransfrom;
    public GameObject photoPrefab;

    private Photo photo;
    private int currentNum = 0;

    // Update is called once per frame
    void Update ()
    {

        if(Input.GetKeyDown(KeyCode.Space))
        {
            
            if (photo == null)
            {
                photo = new Photo();
                photo.Set(sprites[currentNum], canvasTransfrom);
            }
            else
                photo.Change(sprites[currentNum]);

            currentNum = (currentNum + 1) % sprites.Count;
        }
		
	}

    public class Photo
    {
        private Image image;
        private GameObject gameObject;

        public Photo()
        {
            gameObject = new GameObject("Photo");
            image = gameObject.AddComponent<Image>();
        }
        public void Set(Sprite sprite, Transform parent)
        {
            image.sprite = sprite;
            image.SetNativeSize();

            SetOrigin(parent);

        }
        public void SetOrigin(Transform parent)
        {
            gameObject.transform.SetParent(parent);
            gameObject.transform.localPosition = Vector3.zero;
        }
        public void Change(Sprite sprite)
        {
            if (image.sprite == null)
                return;
            image.sprite = sprite;
        }
    }
}
