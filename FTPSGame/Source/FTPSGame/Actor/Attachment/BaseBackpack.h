// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseBackpack.generated.h"

class UDA_WeaponDataAsset;
class ABaseWeapon;

UCLASS()
class FTPSGAME_API ABaseBackpack : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleDefaultsOnly)
	TObjectPtr<USkeletalMeshComponent> Mesh;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UDA_WeaponDataAsset> MainSlotDataAsset = nullptr;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<ABaseWeapon> MainSlotWeapon = nullptr;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UDA_WeaponDataAsset> SubSlotDataAsset = nullptr;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<ABaseWeapon> SubSlotWeapon = nullptr;

public:	
	// Sets default values for this actor's properties
	ABaseBackpack();

	FORCEINLINE USkeletalMeshComponent* GetMesh() { return Mesh; }
	FORCEINLINE ABaseWeapon* GetMainSlotWeapon() { return MainSlotWeapon; }
	FORCEINLINE ABaseWeapon* GetSubSlotWeapon() { return SubSlotWeapon; }
	void SetMainSlot(UDA_WeaponDataAsset* InDataAsset, ABaseWeapon* InWeapon);
	void SetSubSlot(UDA_WeaponDataAsset* InDataAsset, ABaseWeapon* InWeapon);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
