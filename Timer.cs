using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.Events;

public class Timer : MonoBehaviour
{
    [SerializeField]
    private float gameTime = 30.0f;

    [SerializeField]
    private UnityEvent onTimerEnd;

    private Text uiText;
    private float remainTime;

    public bool IsCountingDown { get; private set; }

    void Start()
    {
        uiText = GetComponent<Text>();
        SetTimer(gameTime);

        IsCountingDown = true;
    }

    void Update()
    {
        if (!IsCountingDown)
            return;

        CheckForTimeEnd();
    }

    private void CheckForTimeEnd()
    {
        remainTime -= Time.deltaTime;

        if (remainTime <= 0.0f)
        {
            remainTime = 0.0f;
            IsCountingDown = false;

            if (onTimerEnd != null)
            {
                onTimerEnd.Invoke();
                Debug.Log("Event Invoked");
            }
        }

        uiText.text = string.Format("Remain Time: {0:f}s", remainTime);
    }

    public void SetTimer(float seconds)
    {
        remainTime = seconds;
    }
}
