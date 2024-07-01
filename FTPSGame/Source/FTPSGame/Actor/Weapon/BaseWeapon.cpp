// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Weapon/BaseWeapon.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"

#include "GameFramework/Character.h"
#include "Actor/Character/Hero/Hero.h"
#include "Camera/CameraComponent.h"

#include "Animation/Character_AnimInstance.h"

#include "Utilities/Helper.h"
#include "Components/ArrowComponent.h"

#include "Datas/Weapons/DA_WeaponDataAsset.h"
#include "GameFramework/CharacterMovementComponent.h"

#define ZERO_POINT 25000; //250m to cm

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

void ABaseWeapon::UpdateHitPoint(float DeltaSecond)
{
	AHero* Hero = Cast<AHero>(GetOwner());

	FVector MuzzleLocation = Body->GetSocketLocation("MuzzleFlash");
	HitPoint = MuzzleLocation + GetActorForwardVector() * ZERO_POINT;

	if (Hero == nullptr) return;  // 추후 enemy 용 조건문으로 변경해야 함.


	FHitResult HitResult;
	FVector LineTraceStartPoint = Hero->GetCamera()->GetComponentLocation();
	FVector LineTraceEndPoint = LineTraceStartPoint + Hero->GetCamera()->GetForwardVector() * ZERO_POINT;

	TArray<AActor*> IgnoreActors;
	GetOwner()->GetAllChildActors(IgnoreActors);
	IgnoreActors.Add(GetOwner());

	UKismetSystemLibrary::LineTraceSingle(this, 
		LineTraceStartPoint, LineTraceEndPoint, 
		ETraceTypeQuery::TraceTypeQuery1 /* == Visibility, 2 == Camera */, false, 
		IgnoreActors, 
		EDrawDebugTrace::ForOneFrame, 
		HitResult, 
		true
	);

	if (HitResult.bBlockingHit == false || HitResult.Distance <= 500)
		HitPoint = LineTraceEndPoint;
	else 
		HitPoint = HitResult.ImpactPoint;

	FRotator NewRotation = UKismetMathLibrary::FindLookAtRotation(MuzzleLocation, HitPoint);
	float Speed = 5 / Cast<ACharacter>(GetOwner())->GetCharacterMovement()->RotationRate.Yaw / DeltaSecond;
	if (Hero->IsAiming()) Speed *= 3;
	NewRotation = UKismetMathLibrary::RInterpTo(GetActorRotation(), NewRotation, DeltaSecond, Speed);

	SetActorRotation(NewRotation);

	FHitResult AimHitResult;

	FVector MuzzleEndLocation = MuzzleLocation + GetActorForwardVector() * ZERO_POINT;
	UKismetSystemLibrary::LineTraceSingle(this,
		MuzzleLocation, MuzzleEndLocation,
		ETraceTypeQuery::TraceTypeQuery1 /* == Visibility, 2 == Camera */, false,
		IgnoreActors,
		EDrawDebugTrace::ForOneFrame,
		AimHitResult,
		true
	);

	if (HitResult.bBlockingHit == false)
		HitPoint = MuzzleEndLocation;
	else
		HitPoint = AimHitResult.ImpactPoint;
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

