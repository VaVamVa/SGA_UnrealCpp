// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Move/BTDecorator_IsHostileActorExist.h"

#include "Actor/Character/Enemy/EnemyController.h"
#include "Perception/AIPerceptionComponent.h"

UBTDecorator_IsHostileActorExist::UBTDecorator_IsHostileActorExist()
{
	NodeName = "Check Enemy";
	bNotifyProcessed = true;
}

bool UBTDecorator_IsHostileActorExist::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	AEnemyController* Controller = Cast<AEnemyController>(OwnerComp.GetOwner());

	TArray<AActor*, FDefaultAllocator> OutActors;
	Controller->GetPerceptionComponent()->GetPerceivedHostileActors(OutActors);
	if (OutActors.Num() > 0) return false;
	return true;
}
