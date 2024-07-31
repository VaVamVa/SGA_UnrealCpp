// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseEnemy.generated.h"

class ANavMeshBoundsVolume;

UCLASS()
class FTPSGAME_API ABaseEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category=Team)
	uint8 ID;

private:
	ANavMeshBoundsVolume* NavMeshBound;

public:
	// Sets default values for this character's properties
	ABaseEnemy();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	FORCEINLINE ANavMeshBoundsVolume* GetNavMesh() { return NavMeshBound; }

};
