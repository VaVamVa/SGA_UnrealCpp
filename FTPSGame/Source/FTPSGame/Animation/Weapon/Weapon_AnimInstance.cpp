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
	float AnimLength = 0.0f;  // format : sec
	float DefaultAnimPlayRate = 0.0f;  // format : play rate(speed)

	if (SingleFireAnim)
	{
		AnimLength = SingleFireAnim->GetPlayLength();
		DefaultAnimPlayRate = SingleFireAnim->RateScale;
		SinglePlayRate = RPM / 60.0f * AnimLength / DefaultAnimPlayRate;
	}
	else SinglePlayRate = 1.0f;

	if (AutoFireAnim)
	{
		AnimLength = AutoFireAnim->GetPlayLength();
		DefaultAnimPlayRate = AutoFireAnim->RateScale;
		AutoPlayRate = RPM / 60.0f * AnimLength / DefaultAnimPlayRate;
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
	BulletCounter = OwnerWeapon->GetBulletCounter();


}

void UWeapon_AnimInstance::PreUpdateLinkedInstances(float DeltaSecond)
{
	Super::PreUpdateLinkedInstances(DeltaSecond);

	
}

