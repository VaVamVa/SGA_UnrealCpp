// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"

DECLARE_LOG_CATEGORY_EXTERN(TaskLog, Display, All)

#include "Task_MakeRandomLocation.generated.h"

/**
 * 
 */
UCLASS()
class FTPSGAME_API UTask_MakeRandomLocation : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UTask_MakeRandomLocation();

private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	bool FindNavLocation(const FVector ProjectedLocation, FVector& OutLocation);
	bool FindNavLocation(const float X, const float Y, FVector& OutLocation);
};
