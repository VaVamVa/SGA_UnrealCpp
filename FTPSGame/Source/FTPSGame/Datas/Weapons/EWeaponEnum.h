#pragma once

#include "CoreMinimal.h"

UENUM(Blueprintable)
enum class EWeaponName : uint8
{
	None			UMETA(Hidden),
	Pistol_SA5		,//UMETA(DisplayName = "SA5"),
	Axe_N33			,//UMETA(DisplayName = "N33"),
	Bow_R42			,//UMETA(DisplayName = "R42"),
	Knife_TK5		,//UMETA(DisplayName = "TK5"),
	Launcher_RK53	,//UMETA(DisplayName = "RK53"),
	Pistol_B19		,//UMETA(DisplayName = "B19"),
	Revolver_D22	,//UMETA(DisplayName = "D22"),
	Rifle_M4C		,//UMETA(DisplayName = "M4C"),
	Shotgun_SM12	,//UMETA(DisplayName = "SM12"),
	Smg_XM9			,//UMETA(DisplayName = "XM9"),
	Sniper_L11		,//UMETA(DisplayName = "L11"),
	Sniper_VC30		,//UMETA(DisplayName = "VC30")

};

UENUM(Blueprintable)
enum class EWeaponItemType
{
	Dropped,
	Equipped
};

UENUM(Blueprintable, meta=(Bitflags))
enum class EFireMode : uint8
{
	None					UMETA(Hidden),
	Single,
	Burst,
	Auto,
	End						UMETA(Hidden)
};