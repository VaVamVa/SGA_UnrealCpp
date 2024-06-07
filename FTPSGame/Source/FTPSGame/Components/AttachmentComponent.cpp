// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/AttachmentComponent.h"

#include "Actor/Character/BaseCharacter.h"
#include "Actor/Attachment/BaseBackpack.h"

// Sets default values for this component's properties
UAttachmentComponent::UAttachmentComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	
}


// Called when the game starts
void UAttachmentComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<ABaseCharacter>(GetOwner());

	if (DefaultBackpack != nullptr)
	{
		FActorSpawnParameters Params;
		Params.Owner = OwnerCharacter;
		Backpack = GetWorld()->SpawnActor<ABaseBackpack>(DefaultBackpack, FVector(), FRotator(), Params);

		if (Backpack)
		{
			Backpack->AttachToActor(OwnerCharacter, FAttachmentTransformRules::KeepRelativeTransform);
			Backpack->AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, "Backpack");
		}
	}
	
}


// Called every frame
void UAttachmentComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

