// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Character/Enemy/EnemyController.h"
#include "Perception/AIPerceptionComponent.h"

#include "Perception/AISenseConfig_Sight.h"

#include "BehaviorTree/BehaviorTree.h"

#include "Utilities/Helper.h"

//https://forums.unrealengine.com/t/how-do-i-use-the-ai-perception-teams/120837

AEnemyController::AEnemyController()
{
	BT = Helper::GetAssetFromConstructor<UBehaviorTree>("/Game/Characters/Enemy/BT/BT_Move");

	Perception = Helper::CreateActorComponent<UAIPerceptionComponent>(this, "Perception");
	
	
	Perception->ConfigureSense(*Sight);

}

void AEnemyController::BeginPlay()
{
	Super::BeginPlay();

	RunBehaviorTree(BT);
}

void AEnemyController::UpdateEnemy(const TArray<AActor*>& UpdatedActors)
{
	int index = 233;
	for (auto A : UpdatedActors)
	{
		GEngine->AddOnScreenDebugMessage(index++, 10, FColor::Magenta, A->GetActorLabel());
	}
}
