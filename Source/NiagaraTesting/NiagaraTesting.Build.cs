// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class NiagaraTesting : ModuleRules
{
	public NiagaraTesting(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
  {
      "Core", 
      "CoreUObject", 
      "Engine", 
      "InputCore", 
      "HeadMountedDisplay",
      "Niagara"
  });
	}
}
