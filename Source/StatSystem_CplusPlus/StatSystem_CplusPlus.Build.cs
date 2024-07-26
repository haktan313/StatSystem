// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class StatSystem_CplusPlus : ModuleRules
{
	public StatSystem_CplusPlus(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput" });
	}
}
