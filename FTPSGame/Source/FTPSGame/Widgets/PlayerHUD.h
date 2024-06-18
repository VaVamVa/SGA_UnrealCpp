// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PlayerHUD.generated.h"

/**
 * 
 */

class AHero;
class UCrossHair;

UCLASS()
class FTPSGAME_API APlayerHUD : public AHUD
{
	GENERATED_BODY()
	
	UPROPERTY()
	AHero* Hero;

	UPROPERTY()
	UCrossHair* CrossHair;

	UClass* CrossHairClass;

public:
	APlayerHUD();

	virtual void BeginPlay() override;
	virtual void Tick(float Delta) override;

};
