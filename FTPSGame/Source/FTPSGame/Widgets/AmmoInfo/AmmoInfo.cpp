// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/AmmoInfo/AmmoInfo.h"

#include "Components/TextBlock.h"


void UAmmoInfo::Update(int32 Ammo, int32 Magazine)
{
	FText NewAmmoText = FText::FromString(FString::FromInt(Ammo));
	AmmoText->SetText(NewAmmoText);

	FText NewMagazineText = FText::FromString(FString::FromInt(Magazine));
	MagazineText->SetText(NewMagazineText);
}

void UAmmoInfo::UpdatePosition(FVector2D NewPosition)
{
	SetPositionInViewport(NewPosition, false);
}
