// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class NomNomWarsTarget : TargetRules
{
	public NomNomWarsTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V6;
		IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
		
		// Das hier überschreibt die strengen Überprüfungen für installierte Engines,
		// ohne dass wir das gesamte BuildEnvironment auf Unique setzen müssen.
		bOverrideBuildEnvironment = true; 

		ExtraModuleNames.Add("NomNomWars");
	}
}