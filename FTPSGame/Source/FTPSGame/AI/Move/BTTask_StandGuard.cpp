// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Move/BTTask_StandGuard.h"

UBTTask_StandGuard::UBTTask_StandGuard()
{
	NodeName = "Guard_Observing";
}

EBTNodeResult::Type UBTTask_StandGuard::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return EBTNodeResult::Type();
}

void UBTTask_StandGuard::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float Delta)
{
}
