// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Weapon/Shotgun_SM12.h"
#include "Utilities/Helper.h"

AShotgun_SM12::AShotgun_SM12()
{
	SetMesh(EWeaponName::Shotgun_SM12);

	DataAsset = Helper::GetAssetFromConstructor<UDA_WeaponDataAsset>("/Script/FTPSGame.DA_WeaponDataAsset'/Game/Weapons/1_Blueprint/DA_Shotgun_SM12.DA_Shotgun_SM12'");
}
