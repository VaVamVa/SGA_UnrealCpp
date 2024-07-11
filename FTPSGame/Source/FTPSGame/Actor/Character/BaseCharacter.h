// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

class UDA_WeaponDataAsset;
class ABaseWeapon;
class UInteractComponent;
class UAttachmentComponent;

USTRUCT(Blueprintable)
struct FAnimMontageArray
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly)
	TArray<UAnimMontage*> Montages;
};


UCLASS()
class FTPSGAME_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleDefaultsOnly, meta = (AllowPrivateAccess = true))
	TObjectPtr<UInteractComponent> InteractComp;

	/* 기본 Character Mesh에 Body 할당.
	UPROPERTY(VisibleDefaultsOnly)
	TObjectPtr<USkeletalMeshComponent> Body;
	*/

	UPROPERTY(VisibleDefaultsOnly)
	TObjectPtr<USkeletalMeshComponent> Head;

	UPROPERTY(VisibleDefaultsOnly)
	TObjectPtr<USkeletalMeshComponent> ExoLegs;

	UPROPERTY(VisibleDefaultsOnly)
	TObjectPtr<USkeletalMeshComponent> Laptop;

	UPROPERTY(VisibleDefaultsOnly)
	TObjectPtr<USkeletalMeshComponent> LeftBag;

	UPROPERTY(VisibleDefaultsOnly)
	TObjectPtr<USkeletalMeshComponent> RightBag;

	UPROPERTY(VisibleDefaultsOnly)
	TObjectPtr<USkeletalMeshComponent> ChestBag;

	UPROPERTY(VisibleDefaultsOnly)
	TObjectPtr<USkeletalMeshComponent> LeftGranade;

	UPROPERTY(VisibleDefaultsOnly)
	TObjectPtr<USkeletalMeshComponent> RightGranade;

	UPROPERTY(VisibleDefaultsOnly)
	TObjectPtr<UAttachmentComponent> AttachmentComp;

	// Weapon
	UPROPERTY(EditAnywhere, Category = Weapon, meta = (AllowPrivateAccess = true))
	UDA_WeaponDataAsset* WeaponAsset;

	UPROPERTY(VisibleDefaultsOnly)
	TObjectPtr<UStaticMeshComponent> MagazineMesh;

	// Anim Montage
	UPROPERTY(EditDefaultsOnly, Category = Animation, meta = (AllowPrivateAccess = true))
	TMap<FString, FAnimMontageArray> AnimMontageMap;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	bool bDoSomethingCantCombatAction = false;

	// Aiming
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	bool bAiming = false;
	// Swapping
	bool bSwapping = false;
	// Mirror
	bool bMirrorPlaying = false;

public:
	// Sets default values for this character's properties
	ABaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	virtual void PickUpWeapon(ABaseWeapon* InWeapon);

	virtual void Interact();

	bool PlayCustomMontage(FString Key, float PlayRate = 1.0f, int32 CustomIndex = 0, bool InMirrorPlaying = false);

	FORCEINLINE bool IsAiming() { return bAiming; }
	FORCEINLINE ABaseWeapon* GetEquippedWeapon() { return EquippedWeapon; }

	UFUNCTION()
	void EndSwapping();

	FORCEINLINE bool GetMirror() { return bMirrorPlaying; }
	FORCEINLINE void SetMirror(bool InState) { bMirrorPlaying = InState; }

	void SwapMainSlotWeapon();
	void SwapSubSlotWeapon();

	UFUNCTION(BlueprintNativeEvent)
	void StartAiming();

	UFUNCTION(BlueprintNativeEvent)
	void EndAiming();

	virtual void SwitchFireMode();
	virtual void Fire();
	virtual void HoldFire();

	UFUNCTION()
	void SetAttatchRifle(bool bIsRightHand);

	UFUNCTION()
	void SetVisibleMagazine(bool bVisible);

	virtual void StartReload();

	FORCEINLINE bool GetCantCombatAction() { return bDoSomethingCantCombatAction; }

protected:
	UPROPERTY(VisibleAnywhere, Category = Weapon)
	ABaseWeapon* EquippedWeapon;

	enum ESlot { Main, Sub };
	virtual bool SwapWeapon(ESlot InSlot);

	void SetMagazineMesh();

private:
	void CreateSkeletalMeshComponents();

	
};

