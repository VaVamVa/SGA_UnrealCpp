// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "Service_MakeRandomLocation.generated.h"

/**
 * not good at my logic. just check background action of BTService
 */
UCLASS()
class FTPSGAME_API UService_MakeRandomLocation : public UBTService_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UService_MakeRandomLocation();

private:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
