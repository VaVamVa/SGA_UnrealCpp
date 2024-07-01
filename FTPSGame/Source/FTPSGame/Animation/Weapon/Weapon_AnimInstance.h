// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Weapon_AnimInstance.generated.h"

class ABaseWeapon;
enum class EFireMode : uint8;

/**
 * 
 */
UCLASS()
class FTPSGAME_API UWeapon_AnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
	UPROPERTY()
	ABaseWeapon* OwnerWeapon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	TObjectPtr<UAnimSequence> SingleFireAnim = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	TObjectPtr<UAnimSequence> AutoFireAnim = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	float SinglePlayRate;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	float AutoPlayRate;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	EFireMode FireMode;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	bool bFire;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	bool bChamberEmpty;

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSecond) override;
};
