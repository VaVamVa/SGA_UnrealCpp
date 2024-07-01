// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/Weapon/Weapon_AnimInstance.h"

#include "Actor/Weapon/BaseWeapon.h"
#include "Datas/Weapons/DA_WeaponDataAsset.h"

#include "Datas/Weapons/EWeaponEnum.h"


void UWeapon_AnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	OwnerWeapon = Cast<ABaseWeapon>(GetOwningActor());
}

void UWeapon_AnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();


	float RPM = OwnerWeapon->GetData()->GetRPM();

	if (SingleFireAnim)
	{
		float AnimLength = SingleFireAnim->GetPlayLength();
		SinglePlayRate = RPM / 60.0f / AnimLength;
	}
	else SinglePlayRate = 1.0f;

	if (AutoFireAnim)
	{
		float AnimLength = AutoFireAnim->GetPlayLength();
		AutoPlayRate = RPM / 60.0f / AnimLength;
	}
	else AutoPlayRate = 1.0f;
}

void UWeapon_AnimInstance::NativeUpdateAnimation(float DeltaSecond)
{
	Super::NativeUpdateAnimation(DeltaSecond);

	if (OwnerWeapon == nullptr) return;

	FireMode = OwnerWeapon->GetCurrentFireMode();
	bFire = OwnerWeapon->IsFire();
	bChamberEmpty = OwnerWeapon->IsChamberEmpty();


}

