// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class REST : ModuleRules
{
	public REST(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });

		PrivateDependencyModuleNames.AddRange(new string[] { "Http", "Json", "JsonUtilities" });
	}
}
