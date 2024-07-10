#pragma once

#include "CoreMinimal.h"

UENUM(Blueprintable)
enum class EGeneralInputAction
{
	None UMETA(Hidden),
	Move,
	View
};

UENUM(Blueprintable)
enum class ECombatInputAction
{
	None UMETA(Hidden),
	Interact,
	MainSlot,
	SubSlot,
	Aim,
	Fire,
	SwitchFireMode,
	Reload
};