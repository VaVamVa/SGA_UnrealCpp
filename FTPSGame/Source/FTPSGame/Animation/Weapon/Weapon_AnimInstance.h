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

	// Fire를 False로 바꾸는 부분은 블프에서 구현
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	bool bFire;

	// 위와 동일한 경우
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	bool bChamberEmpty;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	int32 BulletCounter;

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSecond) override;
	void PreUpdateLinkedInstances(float DeltaSecond) override;
};
