// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Weapon/BaseWeapon.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"

#include "GameFramework/Character.h"
#include "Actor/Character/BaseCharacter.h"
#include "Actor/Character/Hero/Hero.h"
#include "Camera/CameraComponent.h"

#include "Animation/Character_AnimInstance.h"

#include "Utilities/Helper.h"
#include "Components/ArrowComponent.h"

#include "Datas/Weapons/DA_WeaponDataAsset.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/TextRenderComponent.h"

#include "Actor/Projectile/Bullet.h"
#include "Engine/StaticMeshActor.h"

#define ZERO_POINT 25000 //250m to cm
#define BURST_BULLET_LIMIT 3  // 3점사

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

	{
		UMaterialInterface* TextMaterial = Helper::GetAssetFromConstructor<UMaterialInterface>("/Game/Widgets/AmmoInfo/GlowTextMaterial");
		
		TextRenderComp = Helper::CreateSceneComponent<UTextRenderComponent>(this, "TextRender", Body);
		TextRenderComp->SetVisibility(false);
		TextRenderComp->SetTextMaterial(TextMaterial);
		TextRenderComp->SetRelativeRotation(FRotator(0, 180, 0));
	}

	/*
	ArrowComp = Helper::CreateSceneComponent<UArrowComponent>(this, "Arrow", Body);
	ArrowComp->SetHiddenInGame(true);
	*/
}

// Called when the game starts or when spawned
void ABaseWeapon::BeginPlay()
{
	Super::BeginPlay();

	CurrentAmmo = DataAsset->GetMaxRonud();
	CurrentMag = DataAsset->GetMaxMagazine();

	{
		//create dynamic material anywhere u like, Constructor or anywhere .
		DynMaterial = UMaterialInstanceDynamic::Create(TextRenderComp->TextMaterial, this);
	}

	//if (ABaseCharacter* TmpOwner = Cast<ABaseCharacter>(GetOwner()))
	//{
	//	EquippedCharacter = TmpOwner;
	//}
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
		//EquippedCharacter = nullptr;
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

		//if (InSocketName == "MainWeapon")
		//	EquippedCharacter = Cast<ABaseCharacter>(InParentComponent->GetOwner());
		//else
		//	EquippedCharacter = nullptr;

		break;
	}
	default:
		break;
	}
}

void ABaseWeapon::SwitchFireMode()
{
	int32 Bit = pow(2, static_cast<int32>(FireMode));
	if (Bit == 0)
		return;

	int32 StartBit = 1;
	while (!(StartBit & DataAsset->GetAvailableFireModes()))
	{
		StartBit = StartBit << 1;
	}

	do
	{
		Bit = Bit << 1;

		if (Bit >= pow(2, static_cast<int32>(EFireMode::End)))
			Bit = StartBit;
	} while (!(Bit & DataAsset->GetAvailableFireModes()));
	
	FireMode = static_cast<EFireMode>(log2(Bit));
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

	GEngine->AddOnScreenDebugMessage(142, 1, FColor::Emerald, FString::FromInt(bFire));
}

void ABaseWeapon::PullTrigger()
{
	if (bChamberEmpty) return;
	//if (FireMode == EFireMode::Burst && BulletCounter != 0) return;
	bFire = true;
	
	/* 람다 함수 이용법. lamda func (?)_have to learn
	if (bFier == false && FireMode == EFireMode::Burst)
	{
		float Time = 60 / DataAsset->GetRPM();
		GetWorldTimerManagaer().SetTimer(BurstHandle, [&]() { bFire = false; }, Time, false);
	}
	*/
}

void ABaseWeapon::ReleaseTrigger()
{
	if (FireMode == EFireMode::Burst) return;
	bFire = false;
	BulletCounter = 0;
}

void ABaseWeapon::UpdateTextFromTextRenderComp()
{
	TextRenderComp->SetText(FText::FromString(FString::FromInt(CurrentAmmo)));
	GEngine->AddOnScreenDebugMessage(1344, 1, FColor::Green, (TextRenderComp->Text).ToString());

	if (CurrentAmmo <= 0)
	{
		DynMaterial->SetVectorParameterValue("GlowColor", FVector(20.0, 0.0, 0.0));
		TextRenderComp->SetTextMaterial(DynMaterial);
	}
	else if (CurrentAmmo <= DataAsset->GetMaxRonud() * 0.5f)
	{
		DynMaterial->SetVectorParameterValue("GlowColor", FVector(20.0, 10.0, 0.0));
		TextRenderComp->SetTextMaterial(DynMaterial);
		//TextRenderComp->SetMaterial(0, DynMaterial);
	}
	else
	{
		DynMaterial->SetVectorParameterValue("GlowColor", FVector(0.0, 5.0, 20.0));
		TextRenderComp->SetTextMaterial(DynMaterial);
	}
}

void ABaseWeapon::SpawnProjectile()
{
	//if (FireMode == EFireMode::Burst)
	//{
	//	BulletCounter++;
	//	if (BulletCounter >= BURST_BULLET_LIMIT)
	//	{
	//		bFire = false;
	//		return;
	//	}
	//}
	if (CurrentAmmo <= 0 || bFire == false) return;



	FTransform Transform = Body->GetSocketTransform("MuzzleFlash");
	FActorSpawnParameters Parameters;
	{
		Parameters.Owner = Owner;
	}
	ABullet* Bullet = GetWorld()->SpawnActor<ABullet>(ABullet::StaticClass(), Transform.GetLocation(), Transform.Rotator(), Parameters);

	BulletCounter++;
	CurrentAmmo--;
	if (AmmoUpdate.IsBound()) AmmoUpdate.Broadcast(CurrentAmmo, CurrentMag);
	//else GEngine->AddOnScreenDebugMessage(12, 3, FColor::Black, "Not Bound AmmoUpdate Delegate");
}

void ABaseWeapon::CheckChamber()
{
	if (CurrentAmmo <= 0)
	{
		bFire = false;
		bChamberEmpty = true;
		BulletCounter = 0;

		return;
	}

	if (CurrentAmmo <= 0 || (FireMode == EFireMode::Burst && BulletCounter >= BURST_BULLET_LIMIT))
	{
		bFire = false;
		BulletCounter = 0;
	}

}

void ABaseWeapon::InitializeWeaponState()
{
	BulletCounter = 0;
	bFire = false;
}

void ABaseWeapon::SetAmmoTextRender(bool Aiming)
{
	TextRenderComp->SetVisibility(Aiming);
}

void ABaseWeapon::SpawnShell()
{
	FTransform Transform = Body->GetSocketTransform("ShellEject");
	FRotator Rotation = UKismetMathLibrary::Quat_Rotator(Transform.GetRotation());

	AStaticMeshActor* Shell = GetWorld()->SpawnActor<AStaticMeshActor>(AStaticMeshActor::StaticClass(), Transform.GetLocation(), Rotation);
	Shell->SetLifeSpan(3);
	Shell->SetMobility(EComponentMobility::Movable);
	Shell->GetStaticMeshComponent()->SetSimulatePhysics(true);
	Shell->GetStaticMeshComponent()->SetStaticMesh(DataAsset->GetShellMesh());
	Shell->GetStaticMeshComponent()->SetCollisionProfileName("ShellProfile");
	
	FVector Force = GetActorRightVector() * 300 + GetActorUpVector() * UKismetMathLibrary::RandomFloatInRange(100, 300);
	Shell->GetStaticMeshComponent()->AddForce(Force);
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

	ABaseCharacter* TmpOwner = Cast<ABaseCharacter>(GetOwner());

	if (TmpOwner == nullptr) return;

	EquippedCharacter = TmpOwner;
	if (EquippedCharacter->IsAiming())
	{
		TextRenderComp->SetWorldLocation(Body->GetSocketLocation("MuzzleFlash"));
		UpdateTextFromTextRenderComp();
		TextRenderComp->SetVisibility(true);
	}
	else
	{
		TextRenderComp->SetVisibility(false);
	}
}

