// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/Character_AnimInstance.h"
#include "Actor/Character/BaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "KismetAnimationLibrary.h"

void UCharacter_AnimInstance::NativeUpdateAnimation(float DeltaSecond)
{
	Super::NativeUpdateAnimation(DeltaSecond);

	if (OwnerCharacter == nullptr) return;
	UpdateBlendSpaceValue();

	// 추후 노티파이 추가되면 노피파이로 처리하자.
	GEngine->AddOnScreenDebugMessage(122, DeltaSecond, FColor::Emerald, FString("Cur Playing Montage Num : ") + FString::FromInt(MontageInstances.Num()));
	GEngine->AddOnScreenDebugMessage(123, DeltaSecond, FColor::Emerald, FString("Cur Mirror : ") + (OwnerCharacter->GetMirror() ? "True" : "False"));
	
	if (MontageInstances.Num() == 0)
		OwnerCharacter->SetMirror(false);
}

void UCharacter_AnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	OwnerCharacter = Cast<ABaseCharacter>(TryGetPawnOwner());
}

void UCharacter_AnimInstance::UpdateBlendSpaceValue()
{
	UCharacterMovementComponent* MovementComponent = OwnerCharacter->GetCharacterMovement();

	if (MovementComponent == nullptr) return;

	bFalling = MovementComponent->IsFalling();

	FVector Velocity = OwnerCharacter->GetVelocity();
	Speed = Velocity.Size2D();

	FRotator Rotation = OwnerCharacter->GetControlRotation();
	Direction = UKismetAnimationLibrary::CalculateDirection(Velocity, Rotation);
}
