// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyController.generated.h"

class UAISenseConfig_Sight;

/**
 * 
 */
UCLASS()
class FTPSGAME_API AEnemyController : public AAIController
{
	GENERATED_BODY()
	
	UPROPERTY()
	UBehaviorTree* BT;

	UPROPERTY()
	UAIPerceptionComponent* Perception;

	UPROPERTY()
	UAISenseConfig_Sight* Sight;

public:
	AEnemyController();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void UpdateEnemy(const TArray<AActor*>& UpdatedActors);
};
