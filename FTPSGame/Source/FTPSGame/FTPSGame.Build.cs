// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class FTPSGame : ModuleRules
{
	public FTPSGame(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core", "CoreUObject", "Engine", 
			"InputCore", "EnhancedInput",
            "AnimGraphRuntime",
			"AIModule",
            "NavigationSystem"
        });

        PublicIncludePaths.Add(ModuleDirectory);
    }
}
