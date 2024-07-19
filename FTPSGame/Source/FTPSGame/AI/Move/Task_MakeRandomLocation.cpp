// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Move/Task_MakeRandomLocation.h"

#include "AI/Navigation/NavigationTypes.h"
#include "NavigationSystem.h"
#include "EngineUtils.h"
#include "NavMesh/NavMeshBoundsVolume.h"

#include "Kismet/KismetMathLibrary.h"

#include "Actor/Character/Enemy/BaseEnemy.h"
#include "Actor/Character/Enemy/EnemyController.h"

#include "BehaviorTree/BlackboardComponent.h"


DEFINE_LOG_CATEGORY(TaskLog);

UTask_MakeRandomLocation::UTask_MakeRandomLocation()
{
	NodeName = "Make Random Location";
}

EBTNodeResult::Type UTask_MakeRandomLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (AEnemyController* Controller = Cast<AEnemyController>(OwnerComp.GetOwner()))
	{
		ABaseEnemy* Enemy = Cast<ABaseEnemy>(Controller->GetCharacter());

		FVector EnemyLocation = Enemy->GetActorLocation();
		for (TActorIterator<ANavMeshBoundsVolume> It(GetWorld()); It; ++It)
		{
			ANavMeshBoundsVolume* NavMeshVolume = *It;
		}
		FVector BoxSize = FVector(500, 500, 0);

		FVector RandomLocation = UKismetMathLibrary::RandomPointInBoundingBox(EnemyLocation, BoxSize);
		FVector NewLocation;
		if (!FindNavLocation(RandomLocation, NewLocation))
		{
			FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
			return EBTNodeResult::Failed;
		}

		if (FVector::Dist(NewLocation, EnemyLocation) < 100)
		{
			FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
			return EBTNodeResult::Failed;
		}


		//while (FVector::Dist(RandomLocation, EnemyLocation) < 100.0)
		//{
		//	RandomLocation = UKismetMathLibrary::RandomPointInBoundingBox(EnemyLocation, BoxSize);
		//	RandomLocation.Z = EnemyLocation.Z;
		//} NewLocation = RandomLocation;

		GEngine->AddOnScreenDebugMessage(3454, 1.0f, FColor::Emerald, NewLocation.ToString());
		OwnerComp.GetBlackboardComponent()->SetValueAsVector("Location", NewLocation);

		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return EBTNodeResult::Succeeded;
	}

	FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	return EBTNodeResult::Failed;
}

bool UTask_MakeRandomLocation::FindNavLocation(const FVector ProjectedLocation, FVector& OutLocation)
{
	UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
	if (!NavSys)
	{
		UE_LOG(TaskLog, Warning, TEXT("Navigation system not found!"));
		return false;
	}

	FNavLocation NavLocation;
	bool bFound = NavSys->ProjectPointToNavigation(ProjectedLocation, NavLocation, FVector(30, 30, 1000));
	if (!bFound)
	{
		UE_LOG(TaskLog, Warning, TEXT("Navigable location not found!"));
		return false;
	}

	OutLocation = NavLocation.Location;
	return true;
}

bool UTask_MakeRandomLocation::FindNavLocation(const float X, const float Y, FVector& OutLocation)
{
	return FindNavLocation(FVector(X, Y, 0), OutLocation);
}
