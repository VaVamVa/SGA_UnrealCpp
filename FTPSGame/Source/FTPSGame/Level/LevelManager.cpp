// Fill out your copyright notice in the Description page of Project Settings.


#include "Level/LevelManager.h"

#include "EngineUtils.h"

#include "Level/BaseNavMeshBounds.h"

ALevelManager::ALevelManager()
{
	LoadNavMeshes();
}

void ALevelManager::BeginPlay()
{
	Super::BeginPlay();
	CoverCurrentNavMeshes();  // Deactive in Serviced game file
}


void ALevelManager::CoverCurrentNavMeshes()
{
	NavMeshes.Empty();
	for (TActorIterator<ANavMeshBoundsVolume> It(GetWorld()); It; ++It)
	{
		ANavMeshBoundsVolume* NavMeshVolume = *It;
		NavMeshes.Add(TTuple<FName, ANavMeshBoundsVolume*>(NavMeshVolume->GetCustomIconName(), NavMeshVolume));
	}
}

void ALevelManager::LoadNavMeshes()
{
	for (TTuple<FName, ANavMeshBoundsVolume*> Elem : NavMeshes)
	{
		ANavMeshBoundsVolume* NavMesh = Elem.Value;
		FActorSpawnParameters Params;
		Params.Name = Elem.Key;
		Params.Owner = this;

		GetWorld()->SpawnActor<ANavMeshBoundsVolume>(
			ANavMeshBoundsVolume::StaticClass(), 
			NavMesh->GetTransform(),
			Params
		);
	}
}
