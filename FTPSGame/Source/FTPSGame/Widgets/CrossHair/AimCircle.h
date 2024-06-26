// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

class UImage;
class AHero;
class ABaseWeapon;

#include "AimCircle.generated.h"

/**
 * 
 */
UCLASS()
class FTPSGAME_API UAimCircle : public UUserWidget
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true, BindWidget))
	TObjectPtr<UImage> Circle;

public:
	void UpdateCirclePosition(ABaseWeapon* InWeapon);  // 자체 Tick 대신. HUD의 Tick에서 Update 시키자.
};
