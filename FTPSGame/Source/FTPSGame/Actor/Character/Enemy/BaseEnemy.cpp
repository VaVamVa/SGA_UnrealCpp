// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Character/Enemy/BaseEnemy.h"

#include "EnemyController.h"
#include "Utilities/Helper.h"

// Sets default values
ABaseEnemy::ABaseEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Mesh
	{
		GetMesh()->SetSkeletalMesh(Helper::GetAssetFromConstructor<USkeletalMesh>("/Game/Legacy/Character/Mannequins/Meshes/SKM_Manny"));
		GetMesh()->SetAnimClass(Helper::GetClassFromConstructor<UAnimInstance>("/Game/Legacy/Character/Mannequins/Animations/ABP_Manny"));
		GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
		GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));
	}

	AIControllerClass = AEnemyController::StaticClass();
}

// Called when the game starts or when spawned
void ABaseEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

