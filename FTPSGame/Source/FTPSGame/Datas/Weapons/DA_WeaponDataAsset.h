// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"

class ABaseWeapon;
class ABaseCharacter;

#include "DA_WeaponDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class FTPSGAME_API UDA_WeaponDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditDefaultsOnly, Category=Property, meta=(AllowOrivateAccess=true))
	TSubclassOf<ABaseWeapon> WeaponClass;

	UPROPERTY(EditDefaultsOnly, Category = Socket, meta = (AllowOrivateAccess = true))
	FName RightHandleSocketName;
	
	UPROPERTY(EditDefaultsOnly, Category = Socket, meta = (AllowOrivateAccess = true))
	FName LeftHandleSocketName;



public:
	UDA_WeaponDataAsset();

	ABaseWeapon* CreateWeapon(ABaseCharacter* InOwner);

	FORCEINLINE FName GetHandleSocketName(bool bRightHandle = true) { return bRightHandle ? RightHandleSocketName : LeftHandleSocketName; }
};
