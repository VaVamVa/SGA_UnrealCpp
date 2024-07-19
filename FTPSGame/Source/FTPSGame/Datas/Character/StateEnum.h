#pragma once

#include "CoreMinimal.h"


// Order is Important

UENUM(BlueprintType)
enum class EState
{
	Dead,
	Hitted,
	Attack,
	Patrol,
	Chase,
	Idle
};
