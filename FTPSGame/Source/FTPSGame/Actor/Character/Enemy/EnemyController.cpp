// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Character/Enemy/EnemyController.h"
#include "Perception/AIPerceptionComponent.h"

#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Damage.h"

#include "BehaviorTree/BehaviorTree.h"

#include "Actor/Character/Enemy/BaseEnemy.h"

#include "Utilities/Helper.h"

//https://forums.unrealengine.com/t/how-do-i-use-the-ai-perception-teams/120837

AEnemyController::AEnemyController()
{
	BT = Helper::GetAssetFromConstructor<UBehaviorTree>("/Game/Characters/Enemy/BT/BT_Move");

	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>("Perception");

	SightSense = CreateDefaultSubobject<UAISenseConfig_Sight>("Sight Sense");
	SightSense->SightRadius = 500.0f;
	SightSense->LoseSightRadius = 700.0f;
	SightSense->PeripheralVisionAngleDegrees = 35.0f;
	SightSense->SetMaxAge(5);
	SightSense->DetectionByAffiliation.bDetectEnemies = true;
	SightSense->DetectionByAffiliation.bDetectNeutrals = false;
	SightSense->DetectionByAffiliation.bDetectFriendlies = false;

	DamageSense = CreateDefaultSubobject<UAISenseConfig_Damage>("Damage Sense");
	DamageSense->SetMaxAge(5);

	PerceptionComponent->ConfigureSense(*SightSense);
	PerceptionComponent->ConfigureSense(*DamageSense);
}

void AEnemyController::BeginPlay()
{
	Super::BeginPlay();

	PerceptionComponent->OnPerceptionUpdated.AddDynamic(this, &AEnemyController::UpdateEnemy);

	
}

void AEnemyController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (BT)
		RunBehaviorTree(BT);;
}

void AEnemyController::OnUnPossess()
{
	Super::OnUnPossess();
}

void AEnemyController::UpdateEnemy(const TArray<AActor*>& UpdatedActors)
{
	PerceptionComponent->RequestStimuliListenerUpdate();  // cache memory에 올라간 team attitude를 초기화
	int index = 233;
	for (auto Actor : UpdatedActors)
	{
		GEngine->AddOnScreenDebugMessage(index++, 10, FColor::Magenta, Actor->GetActorLabel());
		GetTeamAttitudeTowards(*Actor);
	}
}

void AEnemyController::SetGenericTeamId(const FGenericTeamId& NewTeamID)
{
	Super::SetGenericTeamId(NewTeamID);
}

ETeamAttitude::Type AEnemyController::GetTeamAttitudeTowards(const AActor& Other) const
{
	// team 정보 저장?
	/*
	* 1. Game Mode 아마 world가 바뀌면 초기화될것임
	* 2. Level 말 그대로 그 맵에서만 유지
	* 3. GameSession 게임이 실행되는 동안 계속 유지.
	*/
	
	const APawn* OtherPawn = Cast<APawn>(&Other);
	if (OtherPawn == nullptr) return ETeamAttitude::Neutral;

	const ABaseEnemy* OtherEnemy = Cast<ABaseEnemy>(OtherPawn);
	if (OtherEnemy == nullptr) return ETeamAttitude::Hostile;

	if (Cast<ABaseEnemy>(GetCharacter())->ID == OtherEnemy->ID)
		return ETeamAttitude::Friendly;

	return ETeamAttitude::Hostile;
}

void AEnemyController::SetPeripheralVisionDegree(float InDegree)
{
	SightSense->PeripheralVisionAngleDegrees = InDegree;
}