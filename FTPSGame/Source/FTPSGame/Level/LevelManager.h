// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "LevelManager.generated.h"

class ANavMeshBoundsVolume;

/**
 * 
 */
UCLASS()
class FTPSGAME_API ALevelManager : public ALevelScriptActor
{
	GENERATED_BODY()
	
	
	TMap<FName, ANavMeshBoundsVolume*> NavMeshes;

public:
	ALevelManager();

protected:
	virtual void BeginPlay() override;

private:
	void CoverCurrentNavMeshes();
	void LoadNavMeshes();
};
