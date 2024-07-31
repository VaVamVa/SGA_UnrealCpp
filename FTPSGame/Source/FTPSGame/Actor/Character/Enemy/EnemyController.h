// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyController.generated.h"

class UAISenseConfig_Sight;
class UAISenseConfig_Damage;

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
	UAISenseConfig_Sight* SightSense;

	UPROPERTY()
	UAISenseConfig_Damage* DamageSense;

public:
	AEnemyController();

protected:
	virtual void BeginPlay() override;

	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;
private:
	UFUNCTION()
	void UpdateEnemy(const TArray<AActor*>& UpdatedActors);

public:
	virtual void SetGenericTeamId(const FGenericTeamId& NewTeamID) override;
	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;

	void SetPeripheralVisionDegree(float InDegree);
};
