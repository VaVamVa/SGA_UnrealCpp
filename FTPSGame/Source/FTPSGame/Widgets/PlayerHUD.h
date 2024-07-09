// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"

#include "Widgets/CrossHair/CrossHair.h"
#include "Widgets/CrossHair/AimCircle.h"
#include "Widgets/AmmoInfo/AmmoInfo.h"

#include "PlayerHUD.generated.h"
/**
 * 
 */

class AHero;
class UCrossHair;
class UAimCircle;
class UAmmoInfo;

UCLASS()
class FTPSGAME_API APlayerHUD : public AHUD
{
	GENERATED_BODY()
	
	UPROPERTY()
	AHero* Hero;

	UPROPERTY()
	UCrossHair* CrossHair;
	
	UPROPERTY()
	UAimCircle* AimCircle;

	UPROPERTY()
	UAmmoInfo* AmmoInfo;

	UClass* CrossHairClass;
	UClass* AimCircleClass;
	UClass* AmmoInfoClass;

public:
	APlayerHUD();

	virtual void BeginPlay() override;
	virtual void Tick(float Delta) override;

	FORCEINLINE UAmmoInfo* GetAmmoInfo() { return AmmoInfo; }
};
