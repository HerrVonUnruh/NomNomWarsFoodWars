// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class NomNomWarsEditorTarget : TargetRules
{
	public NomNomWarsEditorTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V6;
		IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
		
		// Das sorgt dafür, dass der Editor trotz installierter Engine durchkompiliert
		bOverrideBuildEnvironment = true; 

		ExtraModuleNames.Add("NomNomWars");
	}
}