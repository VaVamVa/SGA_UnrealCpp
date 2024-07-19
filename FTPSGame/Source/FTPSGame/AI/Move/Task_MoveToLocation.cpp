// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Move/Task_MoveToLocation.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Navigation//PathFollowingComponent.h"

#include "Kismet/KismetMathLibrary.h"

#include "Actor/Character/Enemy/BaseEnemy.h"
#include "Actor/Character/Enemy/EnemyController.h"

UTask_MoveToLocation::UTask_MoveToLocation()
{
	bNotifyTick = true;

	NodeName = "Move To Location";

	INIT_TASK_NODE_NOTIFY_FLAGS();
}

EBTNodeResult::Type UTask_MoveToLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (AEnemyController* EnemyController = Cast<AEnemyController>(OwnerComp.GetOwner()))
	{
		Result =
			EnemyController->MoveToLocation(OwnerComp.GetBlackboardComponent()->GetValueAsVector("Location"));
		
		PrevLocation = OwnerComp.GetOwner()->GetActorLocation();

		FinishLatentTask(OwnerComp, EBTNodeResult::InProgress);
		return EBTNodeResult::InProgress;
	}

	FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	return EBTNodeResult::Failed;
}

void UTask_MoveToLocation::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	GEngine->AddOnScreenDebugMessage(13334, 1.0f, FColor::Red, "TickTask");

	if (AEnemyController* EnemyController = Cast<AEnemyController>(OwnerComp.GetOwner()))
	{
		Result = EnemyController->MoveToLocation(OwnerComp.GetBlackboardComponent()->GetValueAsVector("Location"));

		switch (Result)
		{
		case EPathFollowingRequestResult::Failed:
			FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
			break;

		case EPathFollowingRequestResult::AlreadyAtGoal:
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
			break;

		case EPathFollowingRequestResult::RequestSuccessful:
		{
			FVector CurrentLocation = EnemyController->GetCharacter()->GetActorLocation();

			bool CheckMoving = UKismetMathLibrary::NearlyEqual_FloatFloat(CurrentLocation.X, PrevLocation.X,0);
			CheckMoving &= UKismetMathLibrary::NearlyEqual_FloatFloat(CurrentLocation.Y, PrevLocation.Y,0);
			CheckMoving &= UKismetMathLibrary::NearlyEqual_FloatFloat(CurrentLocation.Z, PrevLocation.Z,0);

			GEngine->AddOnScreenDebugMessage(88, 0.5f, FColor::Orange, FString::FromInt(CheckMoving));

			if (CheckMoving)  // 이거 작동 안함.
			{
				StopTime += DeltaSeconds;
			}
			GEngine->AddOnScreenDebugMessage(8, 0.5f, FColor::Orange, FString::SanitizeFloat(StopTime, 3));
			
			if (StopTime > 2.0f)
			{
				StopTime = 0.0f;
				FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
				return;
			}

			PrevLocation = CurrentLocation;

			FinishLatentTask(OwnerComp, EBTNodeResult::InProgress);
			return;
		}
		}

		StopTime = 0.0f;
		return;
	}

	FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
}
