// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Datas/Weapons/FWeaponStruct.h"

#include "Actor/Interface/Interact.h"

class UArrowComponent;
class UDA_WeaponDataAsset;

#include "BaseWeapon.generated.h"

UCLASS()
class FTPSGAME_API ABaseWeapon : public AActor, public IInteract
{
	GENERATED_BODY()

	UPROPERTY(VisibleDefaultsOnly)
	TObjectPtr<USkeletalMeshComponent> Body;

protected:
	UPROPERTY(VisibleDefaultsOnly)
	TObjectPtr<UDA_WeaponDataAsset> DataAsset;

public:
	//UPROPERTY(VisibleDefaultsOnly)
	//TObjectPtr<UArrowComponent> ArrowComp;

protected:
	UPROPERTY(BlueprintReadOnly)
	FString RowName;
	
public:	
	// Sets default values for this actor's properties
	ABaseWeapon();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SetMesh(EWeaponName InWeaponName);

public:	
	virtual void Interact(ABaseCharacter* InCharacter) override;

	void ConversionItemType(EWeaponItemType InType, USceneComponent* InParentComponent = nullptr, FName InSocketName = "");

	FORCEINLINE USkeletalMeshComponent* GetMesh() { return Body; }
	FORCEINLINE UDA_WeaponDataAsset* GetData() { return DataAsset; }


};
