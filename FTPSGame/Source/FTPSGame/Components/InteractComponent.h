// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/CapsuleComponent.h"

class ABaseCharacter;

#include "InteractComponent.generated.h"

/**
 * 
 */
UCLASS()
class FTPSGAME_API UInteractComponent : public UCapsuleComponent
{
	GENERATED_BODY()
	
private:
	UPROPERTY()
	TObjectPtr<ABaseCharacter> OwnerCharacter;

	UPROPERTY()
	TArray<AActor*> InteractObjects;

	UPROPERTY()
	AActor* WinObject;

public:
	UInteractComponent();

	FORCEINLINE AActor* GetWinObject() const { return WinObject; }

protected:
	virtual void BeginPlay() override;

private:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunc) override;

	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
