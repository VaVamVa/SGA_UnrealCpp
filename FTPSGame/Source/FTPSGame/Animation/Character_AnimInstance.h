// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"

class ABaseCharacter;

#include "Character_AnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class FTPSGAME_API UCharacter_AnimInstance : public UAnimInstance
{
	GENERATED_BODY()

	UPROPERTY()
	TObjectPtr<ABaseCharacter> OwnerCharacter;

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Character", meta = (AllowPrivateAccess = true))
	bool bMirror;

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "BlendSpace", meta = (AllowPrivateAccess = true, ClampMin = 0.00))
	float Speed;

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "BlendSpace", meta = (AllowPrivateAccess = true, ClampMin = 0.00))
	float Direction;

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "BlendSpace", meta = (AllowPrivateAccess = true, ClampMin = 0.00))
	bool bFalling;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = IK, meta = (AllowPrivateAccess = true))
	FVector InteractTargetLocation;

public:
	void NativeUpdateAnimation(float DeltaSecond) override;
	void NativeInitializeAnimation() override;

	FORCENOINLINE void SetInteractTargetLocation(FVector InLocation) { InteractTargetLocation = InLocation; }

private:

	void UpdateBlendSpaceValue();

private:
};
