using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[CreateAssetMenu(menuName = "GameSettings")]
public class GameSettings : ScriptableObject
{
    [SerializeField] private float time = 180f;
    public float TimeLimits { get { return time; } }

    [SerializeField] private int chest = 5;
    public int ChestCount { get { return chest; } }

    [SerializeField] private int treasure = 3;
    public int TreasureCount { get { return treasure; } }
}
