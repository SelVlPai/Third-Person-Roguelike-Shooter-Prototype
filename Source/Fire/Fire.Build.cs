// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Fire : ModuleRules
{
    public Fire(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[]
        {
            "Core",
            "CoreUObject",
            "Engine",
            "InputCore",
            "EnhancedInput",
            "AIModule",          // ← ДОБАВИТИ
            "GameplayTasks",     // ← ДОБАВИТИ
            "UMG",               // ← Якщо працюєш з виджетами
            "NavigationSystem", // <- Додати сюди
            "AIModule"          // <- теж обов'язково для BTService / AI
        });

        PrivateDependencyModuleNames.AddRange(new string[]
        {
            "Slate",
            "SlateCore"
        });

        if (Target.bBuildEditor)
        {
            PrivateDependencyModuleNames.Add("UnrealEd");
        }
    }
}
