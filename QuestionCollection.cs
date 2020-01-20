using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[System.Serializable]
public class QuestionCollection
{
    public Question[] questions;

    public string collectionName;

    public override string ToString()
    {
        string result = "QUESTIONS¥n";

        foreach(var question in questions)
        {
            result += string.Format("Question: {0}¥nAnswer: {1}¥n¥n", question.text, question.answer);
        }
        return result;
    }
}
