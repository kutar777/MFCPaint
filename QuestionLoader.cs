using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.IO;
using UnityEngine.UI;
using System;

public class QuestionLoader : MonoBehaviour {

    [SerializeField]
    private string questionPath;

    private QuestionCollection questionCollection;

    [ContextMenu("Load Questions")]
    private void LoadQuestions()
    {
        using (StreamReader stream = new StreamReader(questionPath))
        {
            string json = stream.ReadToEnd();
            questionCollection = JsonUtility.FromJson<QuestionCollection>(json);
        }
        Debug.Log("Questions Loaded: " + questionCollection.questions.Length);
        FindObjectOfType<Text>().text = questionCollection.ToString();
    }

    [ContextMenu("Write Sample Questions")]
    private void WriteSampleQuestions()
    {
        GenerateSampleQuestions();

        using (StreamWriter stream = new StreamWriter(questionPath))
        {
            string json = JsonUtility.ToJson(questionCollection);
            stream.Write(json);
        }
    }

    private void GenerateSampleQuestions()
    {
        Question[] questions = new Question[2];
        questions[0] = new Question() { text = "which question is this?", answer = "number 1" };
        questions[1] = new Question() { text = "Is this the last?", answer = "yes" };

        questionCollection = new QuestionCollection() { questions = questions, collectionName = "sample" };
    }
}
