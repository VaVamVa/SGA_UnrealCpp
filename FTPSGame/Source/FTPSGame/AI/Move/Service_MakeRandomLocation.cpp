// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Move/Service_MakeRandomLocation.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/KismetMathLibrary.h"

#include "Actor/Character/Enemy/BaseEnemy.h"
#include "Actor/Character/Enemy/EnemyController.h"

UService_MakeRandomLocation::UService_MakeRandomLocation()
{
	bNotifyTick = true;
	// tick interval
	Interval = 1.0f;
	// for not orderly tick. seen action naturally
	RandomDeviation = 0.5f;

	NodeName = "Make Random Location Service";
}

void UService_MakeRandomLocation::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	if (AEnemyController* EnemyController = Cast<AEnemyController>(OwnerComp.GetOwner()))
	{
		if (ABaseEnemy* Enemy = Cast<ABaseEnemy>(EnemyController->GetCharacter()))
		{
			FVector EnemyLocation = Enemy->GetActorLocation();
			FVector NewLocation(0);

			UKismetMathLibrary::RandomPointInBoundingBox(EnemyLocation, FVector(300, 300, 0));

			NewLocation.Z = EnemyLocation.Z;

			OwnerComp.GetBlackboardComponent()->SetValueAsVector("Location", NewLocation);
		}
	}
}
