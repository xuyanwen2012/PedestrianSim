// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class MyProjectTarget : TargetRules
{
    public MyProjectTarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Game;

        ExtraModuleNames.AddRange(new[] {"MyProject"});
    }
}