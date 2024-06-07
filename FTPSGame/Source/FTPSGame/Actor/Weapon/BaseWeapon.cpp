// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Weapon/BaseWeapon.h"

#include "Actor/Character/BaseCharacter.h"
#include "Animation/Character_AnimInstance.h"

#include "Utilities/Helper.h"
#include "Components/ArrowComponent.h"

#include "Datas/Weapons/DA_WeaponDataAsset.h"

// Sets default values
ABaseWeapon::ABaseWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Body = Helper::CreateSceneComponent<USkeletalMeshComponent>(this, "Body");

	Body->SetGenerateOverlapEvents(true);

	Body->SetSimulatePhysics(true);
	//Body->SetSimulatePhysics(false);
	Body->SetCollisionProfileName("InteractObject");

	DataAsset = Helper::GetAssetFromConstructor<UDA_WeaponDataAsset>("");

	/*
	ArrowComp = Helper::CreateSceneComponent<UArrowComponent>(this, "Arrow", Body);
	ArrowComp->SetHiddenInGame(true);
	*/
}

void ABaseWeapon::Interact(ABaseCharacter* InCharacter)
{
	FString Key;
	if (InCharacter->IsAiming())
		Key = "Interact_Aiming";
	else
		Key = "Interact_HipFire";

	enum {
		Low, Mid
	};

	int32 CustomIndex;
	if (InCharacter->GetActorLocation().Z - GetActorLocation().Z >= 60.0)
		CustomIndex = static_cast<int32>(Low);
	else
		CustomIndex = static_cast<int32>(Mid);

	Cast<UCharacter_AnimInstance>(InCharacter->GetMesh()->GetAnimInstance())->SetInteractTargetLocation(GetActorLocation());
	InCharacter->SetMirror(false);
	InCharacter->PlayCustommMontage(Key, 1.5f, CustomIndex);

	InCharacter->PickUpWeapon(this);
}

void ABaseWeapon::ConversionItemType(EWeaponItemType InType, USceneComponent* InParentComponent, FName InSocketName)
{
	switch (InType)
	{
	case EWeaponItemType::Dropped:
	{
		Body->SetSimulatePhysics(true);
		Body->SetCollisionProfileName("InteractObject");
		Body->SetGenerateOverlapEvents(true);

		DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		break;
	}
	case EWeaponItemType::Equipped:
	{
		if (InParentComponent == nullptr || InSocketName == "")
		{
			GEngine->AddOnScreenDebugMessage(0, 3, FColor::Red, "Conversion Fail");
			break;
		}

		Body->SetSimulatePhysics(false);
		Body->SetCollisionProfileName("NoCollision");
		Body->SetGenerateOverlapEvents(false);

		AttachToActor(InParentComponent->GetOwner(), FAttachmentTransformRules::KeepRelativeTransform, InSocketName);
		AttachToComponent(InParentComponent, FAttachmentTransformRules::KeepRelativeTransform, InSocketName);

		Body->SetRelativeLocationAndRotation(FVector(0, 0, 0), FRotator(0, 0, 0));

		SetOwner(InParentComponent->GetOwner());

		break;
	}
	default:
		break;
	}
}

// Called when the game starts or when spawned
void ABaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABaseWeapon::SetMesh(EWeaponName InWeaponName)
{
	UDataTable* MeshAssetDataTable = Helper::GetAssetFromConstructor<UDataTable>("/Script/Engine.DataTable'/Game/Weapons/1_Blueprint/WeaponMeshAssetPath.WeaponMeshAssetPath'");

	RowName = UEnum::GetValueAsString(InWeaponName).Replace(L"EWeaponName::", L"");

	FWeaponMeshAssetTable* Data = MeshAssetDataTable->FindRow<FWeaponMeshAssetTable>(FName(RowName), "");
	
	Body->SetSkeletalMesh(Data->SkeletalMesh);
	Body->SetMaterial(0, Data->Skins[3]);
}

// Called every frame
void ABaseWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

