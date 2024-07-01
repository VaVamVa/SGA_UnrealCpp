// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"

class ABaseWeapon;
class ABaseCharacter;
#include "Datas/Weapons/EWeaponEnum.h"

#include "DA_WeaponDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class FTPSGAME_API UDA_WeaponDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditDefaultsOnly, Category=Class, meta=(AllowOrivateAccess=true))
	TSubclassOf<ABaseWeapon> WeaponClass;

	UPROPERTY(EditDefaultsOnly, Category = Socket, meta = (AllowOrivateAccess = true))
	FName RightHandleSocketName;
	
	UPROPERTY(EditDefaultsOnly, Category = Socket, meta = (AllowOrivateAccess = true))
	FName LeftHandleSocketName;

	UPROPERTY(EditDefaultsOnly, Category = Property, meta = (AllowOrivateAccess = true))
	float RoundPerMin = 60;  // 분당 발사 횟수

	UPROPERTY(EditDefaultsOnly, Category = Property, meta = (AllowOrivateAccess = true, Bitmask, BitmaskEnum=EFireMode))
	int32 AvailableFireMpodes = int32(EFireMode::Single);

	UPROPERTY(EditDefaultsOnly, Category = Ammo, meta = (AllowOrivateAccess = true))
	UStaticMesh* ShellMesh;

	UPROPERTY(EditDefaultsOnly, Category = Ammo, meta = (AllowOrivateAccess = true))
	UStaticMesh* MagazineMesh;

	UPROPERTY(EditDefaultsOnly, Category = Ammo, meta = (AllowOrivateAccess = true))
	int32 MaxRound = 1;

	UPROPERTY(EditDefaultsOnly, Category = Ammo, meta = (AllowOrivateAccess = true))
	int32 MaxMagazine = 1;

public:
	UDA_WeaponDataAsset();

	ABaseWeapon* CreateWeapon(ABaseCharacter* InOwner);

	FORCEINLINE FName GetHandleSocketName(bool bRightHandle = true) { return bRightHandle ? RightHandleSocketName : LeftHandleSocketName; }

	FORCEINLINE float GetRPM() const { return RoundPerMin; }
	FORCEINLINE UStaticMesh* GetSehllMesh() const { return ShellMesh; }
	FORCEINLINE UStaticMesh* GetMagazineMesh() const { return MagazineMesh; }
	FORCEINLINE int32 GetMaxRonud() const { return MaxRound; }
	FORCEINLINE int32 GetMaxMagazine() const { return MaxMagazine; }
	FORCEINLINE int32 GetAvailableFireModes() const { return AvailableFireMpodes; }
};
