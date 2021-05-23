// Fill out your copyright notice in the Description page of Project Settings.

using System.IO;
using UnrealBuildTool;

public class LuaProtobuf : ModuleRules
{
	public LuaProtobuf(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core" });

		PrivateDependencyModuleNames.AddRange(new string[] { "Lua" });
		PublicIncludePaths.AddRange(new string[]
		{
			Path.Combine(ModuleDirectory,"Public")
		});
		PublicDefinitions.Add("PB_STATIC_API");
		bEnableShadowVariableWarnings = false;
		bEnableUndefinedIdentifierWarnings = false;

	}
}
