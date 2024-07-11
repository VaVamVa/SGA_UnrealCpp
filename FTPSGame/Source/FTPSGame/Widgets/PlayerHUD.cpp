// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/PlayerHUD.h"
#include "Kismet/GameplayStatics.h"
#include "Actor/Character/Hero/Hero.h"
#include "Camera/CameraComponent.h"

#include "Blueprint/WidgetLayoutLibrary.h"
#include "Kismet/GameplayStatics.h"

#include "Utilities/Helper.h"

APlayerHUD::APlayerHUD()
{
	PrimaryActorTick.bCanEverTick = true;

	CrossHairClass = Helper::GetClassFromConstructor<UUserWidget>("/Game/Widgets/CrossHair/WB_CrossHair");
	AimCircleClass = Helper::GetClassFromConstructor<UUserWidget>("/Game/Widgets/CrossHair/WB_AimCircle");
	AmmoInfoClass = Helper::GetClassFromConstructor<UUserWidget>("/Game/Widgets/AmmoInfo/WB_AmmoInfo");
}

void APlayerHUD::BeginPlay()
{
	Super::BeginPlay();

	Hero = Cast<AHero>(UGameplayStatics::GetPlayerCharacter(this, 0));

	CrossHair = CreateWidget<UCrossHair>(Hero->GetWorld(), CrossHairClass);
	CrossHair->AddToViewport();
	CrossHair->SetVisibility(ESlateVisibility::Visible);

	AimCircle = CreateWidget<UAimCircle>(Hero->GetWorld(), AimCircleClass);
	AimCircle->AddToViewport();
	AimCircle->SetVisibility(ESlateVisibility::Visible);

	AmmoInfo = CreateWidget<UAmmoInfo>(Hero->GetWorld(), AmmoInfoClass);
	AmmoInfo->AddToViewport();
	AmmoInfo->SetVisibility(ESlateVisibility::Visible);
}

void APlayerHUD::Tick(float Delta)
{
	Super::Tick(Delta);

	AimCircle->UpdateCirclePosition(Hero->GetEquippedWeapon());

	// AmmoInfo UI Position
	/*{
		FVector WidgetWorldLocation = Hero->GetMesh()->GetBoneLocation("hand_l");
		WidgetWorldLocation += Hero->GetCamera()->GetRightVector() * 100;

		FVector2D NewPosition;
		UWidgetLayoutLibrary::ProjectWorldLocationToWidgetPosition(UGameplayStatics::GetPlayerController(GetWorld(), 0), WidgetWorldLocation, NewPosition, true);

		AmmoInfo->UpdatePosition(NewPosition);
	}*/
}
