// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Tore : ModuleRules
{
	public Tore(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.Add(ModuleDirectory);
	
		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core",
			
		});
			
		
		PrivateDependencyModuleNames.AddRange(
		new string[]
		{
			"CoreUObject",
			"Engine",
			"Slate",
			"SlateCore",
			"UnrealEd"
		});
		
	}
}
