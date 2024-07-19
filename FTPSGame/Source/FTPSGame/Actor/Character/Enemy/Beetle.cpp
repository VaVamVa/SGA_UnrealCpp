// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Character/Enemy/Beetle.h"

#include "EnemyController.h"
#include "Utilities/Helper.h"

ABeetle::ABeetle()
{
	PrimaryActorTick.bCanEverTick = true;

	// Mesh
	{
		GetMesh()->SetSkeletalMesh(Helper::GetAssetFromConstructor<USkeletalMesh>("/Script/Engine.SkeletalMesh'/Game/Characters/Enemy/Bloodthirsty_beetle/Mesh/SK_Bloodthirsty_beetle.SK_Bloodthirsty_beetle'"));
		//GetMesh()->SetAnimClass(Helper::GetClassFromConstructor<UAnimInstance>("/Game/Animation/AnimInstance/BP_Beetle_AnimInstance"));
		GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
		GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));
	}

	AIControllerClass = AEnemyController::StaticClass();
}

void ABeetle::BeginPlay()
{
	Super::BeginPlay();

	
	GetWorld()->GetTimerManager().SetTimer(MyTimer, this, &ABeetle::OnTimer, 1.0f, true);
}

void ABeetle::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	GetWorld()->GetTimerManager().ClearTimer(MyTimer);
}

void ABeetle::OnTimer()
{
	TimerCount++;

	if (TimerCount > 5)
	{
		GEngine->AddOnScreenDebugMessage(233, 1.0f, FColor::Red, "Boolean Change Action");
		TimerCount = 0;
		bMove = !bMove;
	}
}
