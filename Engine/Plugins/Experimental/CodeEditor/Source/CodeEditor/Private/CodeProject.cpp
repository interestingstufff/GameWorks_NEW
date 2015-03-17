// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "CodeEditorPrivatePCH.h"
#include "CodeProject.h"

UCodeProject::UCodeProject(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	Path = FPaths::GameSourceDir();
}
