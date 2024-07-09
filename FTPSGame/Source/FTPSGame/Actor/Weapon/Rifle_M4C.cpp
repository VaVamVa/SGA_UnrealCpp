// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Weapon/Rifle_M4C.h"
#include "Datas/Weapons/DA_WeaponDataAsset.h"
#include "Utilities/Helper.h"

ARifle_M4C::ARifle_M4C()
{
	SetMesh(EWeaponName::Rifle_M4C);

	DataAsset = Helper::GetAssetFromConstructor<UDA_WeaponDataAsset>("/Game/Weapons/1_Blueprint/DA_Rifle_M4C");

	Body->SetAnimInstanceClass(Helper::GetClassFromConstructor<UAnimInstance>("/Game/Weapons/RifleM4C/Animations/RifleM4C_AnimInBlueprint"));
}

void ARifle_M4C::PullTrigger()
{
	Super::PullTrigger();


}
