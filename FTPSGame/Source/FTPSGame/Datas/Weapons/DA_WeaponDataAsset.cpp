// Fill out your copyright notice in the Description page of Project Settings.


#include "Datas/Weapons/DA_WeaponDataAsset.h"

#include "Actor/Weapon/BaseWeapon.h"
#include "Actor/Character/BaseCharacter.h"

UDA_WeaponDataAsset::UDA_WeaponDataAsset()
{
}

ABaseWeapon* UDA_WeaponDataAsset::CreateWeapon(ABaseCharacter* InOwner)
{
	FActorSpawnParameters Parameters;
	Parameters.Owner = InOwner;
	
	ABaseWeapon* OutWeapon = InOwner->GetWorld()->SpawnActor<ABaseWeapon>
		(
		WeaponClass, FVector(), FRotator(), Parameters
		);

	OutWeapon->GetMesh()->SetSimulatePhysics(false);
	OutWeapon->GetMesh()->SetCollisionProfileName("NoCollision");

	return OutWeapon;
}
