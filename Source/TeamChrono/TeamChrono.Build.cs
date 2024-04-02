// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TeamChrono : ModuleRules
{
	public TeamChrono(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] 
		{
			"Core", 
			"CoreUObject", 
			"Engine",
			"InputCore", 
			"EnhancedInput", 
			"AIModule",
			"GameplayTasks",
			"NavigationSystem",
			"UMG",
			"Niagara"
		});
	}
}
