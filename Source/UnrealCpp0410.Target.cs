// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class UnrealCpp0410Target : TargetRules
{
	public UnrealCpp0410Target(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.Latest;
		IncludeOrderVersion = EngineIncludeOrderVersion.Latest;


        ExtraModuleNames.AddRange( new string[] { "UnrealCpp0410" } );
	}
}
