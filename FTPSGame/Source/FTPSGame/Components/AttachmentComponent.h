// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AttachmentComponent.generated.h"

class ABaseCharacter;
class ABaseBackpack;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FTPSGAME_API UAttachmentComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY()
	ABaseCharacter* OwnerCharacter;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ABaseBackpack> DefaultBackpack;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<ABaseBackpack> Backpack;

public:	
	// Sets default values for this component's properties
	UAttachmentComponent();

	FORCEINLINE ABaseBackpack* GetBackpack() const { return Backpack; }

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
