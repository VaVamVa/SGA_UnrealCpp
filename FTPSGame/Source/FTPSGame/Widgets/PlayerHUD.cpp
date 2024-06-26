// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/PlayerHUD.h"
#include "Kismet/GameplayStatics.h"
#include "Actor/Character/Hero/Hero.h"

#include "Widgets/CrossHair/CrossHair.h"
#include "Widgets/CrossHair/AimCircle.h"

#include "Utilities/Helper.h"

APlayerHUD::APlayerHUD()
{
	PrimaryActorTick.bCanEverTick = true;

	CrossHairClass = Helper::GetClassFromConstructor<UUserWidget>("/Game/Widgets/CrossHair/WB_CrossHair");
	AimCircleClass = Helper::GetClassFromConstructor<UUserWidget>("/Game/Widgets/CrossHair/WB_AimCircle");
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
}

void APlayerHUD::Tick(float Delta)
{
	Super::Tick(Delta);

	AimCircle->UpdateCirclePosition(Hero->GetEquippedWeapon());
}
