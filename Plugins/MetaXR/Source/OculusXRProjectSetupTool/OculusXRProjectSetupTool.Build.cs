﻿// Copyright (c) Meta Platforms, Inc. and affiliates.

using UnrealBuildTool;

public class OculusXRProjectSetupTool : ModuleRules
{
	public OculusXRProjectSetupTool(ReadOnlyTargetRules Target) : base(Target)
	{

		bUseUnity = true;

		PrivateIncludePaths.AddRange(
			new string[] {
				"OculusXRHMD/Private",
			});

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"CoreUObject",
				"Engine"
			}
		);

		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"Projects",
				"UnrealEd",
				"LevelEditor",
				"Slate",
				"SlateCore",
				"EditorStyle",
				"EngineSettings",
				"OculusXRHMD",
				"OculusXRMovement",
				"OculusXRPassthrough",
				"OculusXRAnchors",
				"OculusXRScene",
				"AndroidRuntimeSettings",
				"LauncherServices",
				"ToolWidgets",
				"WorkspaceMenuStructure",
				"PluginBrowser",
				"ToolMenus"
			}
		);
	}
}
