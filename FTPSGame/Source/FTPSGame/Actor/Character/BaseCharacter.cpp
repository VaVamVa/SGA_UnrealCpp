// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Character/BaseCharacter.h"
#include "Utilities/Helper.h"

#include "Components/InteractComponent.h"
#include "Components/AttachmentComponent.h"

#include "Datas/Equipment/EquipmentStruct.h"

#include "Datas/Weapons/DA_WeaponDataAsset.h"
#include "Actor/Weapon/BaseWeapon.h"
#include "Actor/Attachment/BaseBackpack.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	

	CreateSkeletalMeshComponents();

	//GetMesh()->Rename(L"Body");
	GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	GetMesh()->SetAnimClass(Helper::GetClassFromConstructor<UAnimInstance>("/Script/Engine.AnimBlueprint'/Game/Animation/AnimInstance/BP_Character_AnimInstance.BP_Character_AnimInstance'"));

	InteractComp = Helper::CreateSceneComponent<UInteractComponent>(this, "InteractComponent", RootComponent);
	AttachmentComp = Helper::CreateActorComponent<UAttachmentComponent>(this, "AttachmentComponent");

	//ConstructorHelpers::FObjectFinder<UDataTable> Finder(L"/Game/Equipment/DT_EquipmentMesh");
	//UDataTable* SkeletalMeshData = nullptr;
	//if (Finder.Succeeded())
	//	UDataTable* SkeletalMeshData = Finder.Object;
	UDataTable* SkeletalMeshData = Helper::GetAssetFromConstructor<UDataTable>("/Game/Equipment/DT_EquipmentMesh");
	FEquipmentMeshAsset* Asset = nullptr;

	// body
	Asset = SkeletalMeshData->FindRow<FEquipmentMeshAsset>(FName("Body"), ""/*log msg*/);
	if (Asset) GetMesh()->SetSkeletalMesh(Asset->SkeletalMesh[0]);

	// head
	Asset = SkeletalMeshData->FindRow<FEquipmentMeshAsset>(FName("Head"), ""/*log msg*/);
	if (Asset) Head->SetSkeletalMesh(Asset->SkeletalMesh[0]);


	// Motages Setting
	{
		FAnimMontageArray TempMontages;
		TempMontages.Montages.AddUnique(Helper::GetAssetFromConstructor<UAnimMontage>("/Script/Engine.AnimMontage'/Game/Animation/Montages/HipFire_St_PickUp_Low_Montage.HipFire_St_PickUp_Low_Montage'"));
		TempMontages.Montages.AddUnique(Helper::GetAssetFromConstructor<UAnimMontage>("/Script/Engine.AnimMontage'/Game/Animation/Montages/HipFire_St_PickUp_Mid_Montage.HipFire_St_PickUp_Mid_Montage'"));
		AnimMontageMap.Add("Interact_HipFire", TempMontages);

		TempMontages.Montages.Empty();
		TempMontages.Montages.AddUnique(Helper::GetAssetFromConstructor<UAnimMontage>("/Script/Engine.AnimMontage'/Game/Animation/Montages/Aim_St_PickUp_Low_Montage.Aim_St_PickUp_Low_Montage'"));
		TempMontages.Montages.AddUnique(Helper::GetAssetFromConstructor<UAnimMontage>("/Script/Engine.AnimMontage'/Game/Animation/Montages/Aim_St_PickUp_Mid_Montage.Aim_St_PickUp_Mid_Montage'"));
		AnimMontageMap.Add("Interact_Aim", TempMontages);

		TempMontages.Montages.Empty();
		TempMontages.Montages.AddUnique(Helper::GetAssetFromConstructor<UAnimMontage>("/Script/Engine.AnimMontage'/Game/Animation/Montages/Swap/HipFire_St_TakeDown_Montage.HipFire_St_TakeDown_Montage'"));
		TempMontages.Montages.AddUnique(Helper::GetAssetFromConstructor<UAnimMontage>("/Script/Engine.AnimMontage'/Game/Animation/Montages/Swap/Aim_St_TakeDown_Montage.Aim_St_TakeDown_Montage'"));
		AnimMontageMap.Add("Swapping", TempMontages);
	}
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	

	if (WeaponAsset)
		EquippedWeapon = WeaponAsset->CreateWeapon(this);

	if (EquippedWeapon)
	{
		EquippedWeapon->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
		EquippedWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, WeaponAsset->GetHandleSocketName());
	}
}

void ABaseCharacter::SwapMainSlotWeapon()
{
	SwapWeapon(ESlot::Main);
}

void ABaseCharacter::SwapSubSlotWeapon()
{
	SwapWeapon(ESlot::Sub);
}

void ABaseCharacter::SwapWeapon(ESlot InSlot)
{
	if (bSwapping == true) return;
	//bSwapping = true;
	bMirrorPlaying = false;

	ABaseWeapon* SelectedWeapon = nullptr;
	FName SocketName = "";
	ABaseBackpack* Backpack = AttachmentComp->GetBackpack();
	if (Backpack != nullptr)
	{
		switch (InSlot)
		{
		case ABaseCharacter::Main:
		{
			SelectedWeapon = Backpack->GetMainSlotWeapon();
			SocketName = "MainSlot";
		}
			break;
		case ABaseCharacter::Sub:
		{
			SelectedWeapon = Backpack->GetSubSlotWeapon();
			SocketName = "SubSlot";
			bMirrorPlaying = true;
		}
			break;
		default:
			break;
		}
	}

	if (SelectedWeapon != nullptr)
	{
		PlayCustommMontage("Swapping", 1.0f, bAiming, bMirrorPlaying);  // false == HipFire

		EquippedWeapon->ConversionItemType(EWeaponItemType::Equipped, Backpack->GetMesh(), SocketName);
		SelectedWeapon->ConversionItemType(EWeaponItemType::Equipped, GetMesh(), SelectedWeapon->GetData()->GetHandleSocketName());

		Swap(EquippedWeapon, SelectedWeapon);
		WeaponAsset = EquippedWeapon->GetData();
		
		InSlot == ESlot::Main ?
			Backpack->SetMainSlot(SelectedWeapon->GetData(), SelectedWeapon) :
			Backpack->SetSubSlot(SelectedWeapon->GetData(), SelectedWeapon);
	}
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	GEngine->AddOnScreenDebugMessage(125, 0.2, FColor::Blue, FString("Cur Mirror : ") + (bMirrorPlaying ? "True" : "False"));
}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABaseCharacter::PickUpWeapon(ABaseWeapon* InWeapon)
{
	if (ABaseBackpack* Backpack = AttachmentComp->GetBackpack())
	{
		if (Backpack->GetMainSlotWeapon() == nullptr)
		{
			InWeapon->ConversionItemType(EWeaponItemType::Equipped, Backpack->GetMesh(), "MainSlot");
			Backpack->SetMainSlot(InWeapon->GetData(), InWeapon);
			return;
		}
		if (Backpack->GetSubSlotWeapon() == nullptr)
		{
			InWeapon->ConversionItemType(EWeaponItemType::Equipped, Backpack->GetMesh(), "SubSlot");
			Backpack->SetSubSlot(InWeapon->GetData(), InWeapon);
			return;
		}
	}
	
	// 장착되어있던 무기 드랍
	EquippedWeapon->ConversionItemType(EWeaponItemType::Dropped);

	// 바닥에 있는 무기 손에 장착
	InWeapon->ConversionItemType(EWeaponItemType::Equipped, GetMesh(), InWeapon->GetData()->GetHandleSocketName());

	EquippedWeapon = InWeapon;
	WeaponAsset = InWeapon->GetData();
}

void ABaseCharacter::Interact()
{
	if (IInteract* Object = Cast<IInteract>(InteractComp->GetWinObject()))
		Object->Interact(this);
}

void ABaseCharacter::PlayCustommMontage(FString Key, float PlayRate, int32 CustomIndex, bool InMirrorPlaying)
{
	UAnimMontage* Montage = AnimMontageMap.Find(Key)->Montages[CustomIndex];

	bMirrorPlaying = InMirrorPlaying;
	PlayAnimMontage(Montage, PlayRate);
}

void ABaseCharacter::CreateSkeletalMeshComponents()
{
	Head = Helper::CreateSceneComponent<USkeletalMeshComponent>(this, "Head", GetMesh());
	ExoLegs = Helper::CreateSceneComponent<USkeletalMeshComponent>(this, "ExoLegs", GetMesh());
	Laptop = Helper::CreateSceneComponent<USkeletalMeshComponent>(this, "Laptop", GetMesh());
	LeftBag = Helper::CreateSceneComponent<USkeletalMeshComponent>(this, "LeftBag", GetMesh());
	RightBag = Helper::CreateSceneComponent<USkeletalMeshComponent>(this, "RightBag", GetMesh());
	ChestBag = Helper::CreateSceneComponent<USkeletalMeshComponent>(this, "ChestBag", GetMesh());
	LeftGranade = Helper::CreateSceneComponent<USkeletalMeshComponent>(this, "LeftGranade", GetMesh());
	RightGranade = Helper::CreateSceneComponent<USkeletalMeshComponent>(this, "RightGranade", GetMesh());

	Head->SetLeaderPoseComponent(GetMesh());
	ExoLegs->SetLeaderPoseComponent(GetMesh());
	Laptop->SetLeaderPoseComponent(GetMesh());
	LeftBag->SetLeaderPoseComponent(GetMesh());
	RightBag->SetLeaderPoseComponent(GetMesh());
	ChestBag->SetLeaderPoseComponent(GetMesh());
	LeftGranade->SetLeaderPoseComponent(GetMesh());
	RightGranade->SetLeaderPoseComponent(GetMesh());
}

