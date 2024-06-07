// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Attachment/BaseBackpack.h"

#include "Utilities/Helper.h"

#include "Datas/Weapons/DA_WeaponDataAsset.h"
#include "Actor/Weapon/BaseWeapon.h"

// Sets default values
ABaseBackpack::ABaseBackpack()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = Helper::CreateSceneComponent<USkeletalMeshComponent>(this, "Mesh");
	Mesh->SetSkeletalMesh(Helper::GetAssetFromConstructor<USkeletalMesh>("/Script/Engine.SkeletalMesh'/Game/Characters/Elite_Solders/BackPack/SK_Backpack.SK_Backpack'"));

}

void ABaseBackpack::SetMainSlot(UDA_WeaponDataAsset* InDataAsset, ABaseWeapon* InWeapon)
{
	MainSlotDataAsset = InDataAsset;
	MainSlotWeapon = InWeapon;
}

void ABaseBackpack::SetSubSlot(UDA_WeaponDataAsset* InDataAsset, ABaseWeapon* InWeapon)
{
	SubSlotDataAsset = InDataAsset;
	SubSlotWeapon = InWeapon;
}

// Called when the game starts or when spawned
void ABaseBackpack::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseBackpack::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

