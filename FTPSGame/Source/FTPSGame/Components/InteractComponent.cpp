#include "Components/InteractComponent.h"

#include "Actor/Character/BaseCharacter.h"
#include "Actor/Weapon/BaseWeapon.h"
#include "Components/ArrowComponent.h"

#include "Actor/Interface/Interact.h"

#include "Kismet/KismetMathLibrary.h"

UInteractComponent::UInteractComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = true;
	PrimaryComponentTick.SetTickFunctionEnable(true);
	
	UPrimitiveComponent::SetCollisionProfileName("InteractCollision");

	if (GetOwner())
		OwnerCharacter = Cast<ABaseCharacter>(GetOwner());

	if (OwnerCharacter == nullptr) return;

	CapsuleRadius = OwnerCharacter->GetCapsuleComponent()->GetScaledCapsuleRadius() * 2.0f;
	CapsuleHalfHeight = OwnerCharacter->GetCapsuleComponent()->GetScaledCapsuleHalfHeight() * 1.5f;
}

void UInteractComponent::BeginPlay()
{
	Super::BeginPlay();
	SetComponentTickEnabled(true);

	OwnerCharacter = Cast<ABaseCharacter>(GetOwner());

	OnComponentBeginOverlap.AddDynamic(this, &UInteractComponent::BeginOverlap);
	OnComponentEndOverlap.AddDynamic(this, &UInteractComponent::EndOverlap);

	SetHiddenInGame(false);

	//GEngine->AddOnScreenDebugMessage(0, 3, FColor::Black, FString::FromInt(PrimaryComponentTick.IsTickFunctionEnabled()));
	//GEngine->AddOnScreenDebugMessage(1, 3, FColor::Cyan, FString::FromInt(PrimaryComponentTick.TickGroup.GetIntValue()));
	//GEngine->AddOnScreenDebugMessage(2, 3, FColor::Black, FString::FromInt(PrimaryComponentTick.bStartWithTickEnabled));
	//GEngine->AddOnScreenDebugMessage(3, 3, FColor::White, FString::FromInt(PrimaryComponentTick.bCanEverTick));

}

void UInteractComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunc)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunc);

	if (InteractObjects.Num() <= 0) 
	{
		if (WinObject) 
		{
			//Cast<ABaseWeapon>(WinObject)->ArrowComp->SetHiddenInGame(true);
			WinObject = nullptr;
		}
		return; 
	}

	float WinObjectTotalScore = -FLT_MAX;
	
	float DistanceScore = 0.0f;
	float LookingScore = 0.0f;
	
	for (auto* Object : InteractObjects)
	{
		DistanceScore = OwnerCharacter->GetDistanceTo(Object) * -0.2f;  // °¡±î¿ï ¼ö·Ï Àý´ë°ª ³·¾ÆÁü -> À½¼ö´Â Ä¿Áü

		FVector ForwardVector = UKismetMathLibrary::GetForwardVector(OwnerCharacter->GetControlRotation());
		
		if (ForwardVector.Z > -0.45f)
			LookingScore = 0.0f;
		else
			LookingScore = UKismetMathLibrary::GetPointDistanceToLine(Object->GetActorLocation(), OwnerCharacter->GetActorLocation(), ForwardVector) * -0.8f;

		if (WinObjectTotalScore < DistanceScore + LookingScore)
		{
			//if (WinObject != nullptr && WinObject != Object)
			//	Cast<ABaseWeapon>(WinObject)->ArrowComp->SetHiddenInGame(true);

			WinObjectTotalScore = DistanceScore + LookingScore;
			WinObject = Object;
			//Cast<ABaseWeapon>(WinObject)->ArrowComp->SetHiddenInGame(false);
		}
	}

	GEngine->AddOnScreenDebugMessage(0, 0.3f, FColor::Green, WinObject ? WinObject->GetActorLabel() : "None");
	
	/* debugging
	for (int i = 0; i < InteractObjects.Num(); i++)
	{
		GEngine->AddOnScreenDebugMessage(i, 0.3f, FColor::Green, InteractObjects[i]->GetActorLabel());
	}
	*/

}

void UInteractComponent::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	InteractObjects.AddUnique(OtherActor);

	//GEngine->AddOnScreenDebugMessage(OtherBodyIndex, 3, FColor::Blue, OtherActor->GetActorLabel());
	
}

void UInteractComponent::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	InteractObjects.Remove(OtherActor);
	
	//GEngine->AddOnScreenDebugMessage(OtherBodyIndex, 3, FColor::Red, OtherActor->GetActorLabel());
}
