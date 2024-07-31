// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_StandGuard.generated.h"

/**
 * 
 */
UCLASS()
class FTPSGAME_API UBTTask_StandGuard : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	

public:
	UBTTask_StandGuard();

private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float Delta) override;

};
