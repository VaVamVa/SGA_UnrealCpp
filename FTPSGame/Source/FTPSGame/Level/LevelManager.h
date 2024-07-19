// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "LevelManager.generated.h"

class BaseNavMesh;

/**
 * 
 */
UCLASS()
class FTPSGAME_API ALevelManager : public ALevelScriptActor
{
	GENERATED_BODY()
	
	// DistrictName, BaseNaveMeshBound Ptr
	TMap<FName, BaseNavMesh*> NavMeshes;
};
