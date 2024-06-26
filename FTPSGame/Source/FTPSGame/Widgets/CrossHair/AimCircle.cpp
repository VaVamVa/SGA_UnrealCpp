// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/CrossHair/AimCircle.h"

#include "Blueprint/WidgetLayoutLibrary.h"
#include "Kismet/GameplayStatics.h"

#include "Actor/Character/Hero/Hero.h"
#include "Actor/Weapon/BaseWeapon.h"

void UAimCircle::UpdateCirclePosition(ABaseWeapon* InWeapon)
{
	FVector2D NewPosition;
	
	UWidgetLayoutLibrary::ProjectWorldLocationToWidgetPosition(UGameplayStatics::GetPlayerController(InWeapon->GetWorld(), 0), InWeapon->GetHitPoint(), NewPosition, false);

	SetPositionInViewport(NewPosition, false);  // Project (Convert Viewport about 3D -> 2D)

}
