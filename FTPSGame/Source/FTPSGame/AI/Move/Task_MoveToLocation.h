// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "Task_MoveToLocation.generated.h"

namespace EPathFollowingRequestResult
{
	enum Type : int;
}

/**
 * 
 */
UCLASS()
class FTPSGAME_API UTask_MoveToLocation : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

	EPathFollowingRequestResult::Type Result;

	float StopTime = 0.0f;
	FVector PrevLocation;

public:
	UTask_MoveToLocation();
	
private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
