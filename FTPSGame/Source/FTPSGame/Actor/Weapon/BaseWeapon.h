// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Datas/Weapons/EWeaponEnum.h"
#include "Datas/Weapons/FWeaponStruct.h"

#include "Actor/Interface/Interact.h"

class UArrowComponent;
class UDA_WeaponDataAsset;
class UTextRenderComponent;
class ABaseCharacter;

#include "BaseWeapon.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FAmmoUpdate, int32, Ammo, int32, Magazine);

UCLASS()
class FTPSGAME_API ABaseWeapon : public AActor, public IInteract
{
	GENERATED_BODY()


	bool bFire = false;
	bool bChamberEmpty = false;
	EFireMode FireMode = EFireMode::Single;
	
	int32 BulletCounter = 0;
	int32 CurrentAmmo;
	int32 CurrentMag;

	UPROPERTY(VisibleDefaultsOnly)
	TObjectPtr<UTextRenderComponent> TextRenderComp;

	UMaterialInstanceDynamic* DynMaterial;

	UPROPERTY()
	TObjectPtr<ABaseCharacter> EquippedCharacter;

protected:
	UPROPERTY(VisibleDefaultsOnly)
	TObjectPtr<UDA_WeaponDataAsset> DataAsset;

	UPROPERTY(VisibleDefaultsOnly)
	TObjectPtr<USkeletalMeshComponent> Body;

	UPROPERTY(VisibleDefaultsOnly)
	TObjectPtr<UStaticMeshComponent> Magazine;

protected:
	UPROPERTY(BlueprintReadOnly)
	FString RowName;
	
	FVector HitPoint;

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

	void SwitchFireMode();

	FORCEINLINE bool IsFire() const { return bFire; }
	FORCEINLINE bool IsChamberEmpty() const { return bChamberEmpty; }
	FORCEINLINE uint8 GetBulletCounter() const { return BulletCounter; }
	FORCEINLINE USkeletalMeshComponent* GetMesh() const { return Body; }
	FORCEINLINE UDA_WeaponDataAsset* GetData() const { return DataAsset; }
	FORCEINLINE FVector GetHitPoint() const { return HitPoint; }
	FORCEINLINE EFireMode GetCurrentFireMode() const { return FireMode; }
	FORCEINLINE int32 GetCurrentAmmo() const { return CurrentAmmo; }
	FORCEINLINE int32 GetCurrentMag() const { return CurrentMag; }

	void UpdateHitPoint(float DeltaSecond);
	
	virtual void PullTrigger();
	virtual void ReleaseTrigger();

	FAmmoUpdate AmmoUpdate;

	void UpdateTextFromTextRenderComp();
	
	enum TEXT_COLOR
	{
		Blue, Yellow, Red, Max
	};
	FVector TextColors[TEXT_COLOR::Max] =
	{
		FVector(0, 5, 15), FVector(10, 10, 0), FVector(20, 0, 0)
	};

public:  // Notify
	UFUNCTION()
	void SpawnProjectile();

	UFUNCTION()
	void CheckChamber();

	UFUNCTION()
	void InitializeWeaponState();

	UFUNCTION()
	void SwitchAmmoTextRender(bool Aiming);

	// Reload
	UFUNCTION()
	void SwapMagazine(bool bBeingSwap);


protected:
	UFUNCTION()
	virtual void SpawnShell();

	UFUNCTION()
	void SpawnDropMagazine();
};
