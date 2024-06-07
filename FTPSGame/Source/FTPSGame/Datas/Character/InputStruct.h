#pragma once

#include "CoreMinimal.h"
#include "InputEnum.h"

class UInputAction;
class UInputMappingContext;

#include "InputStruct.generated.h"

USTRUCT(Blueprintable)
struct FGeneralInputMapping
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, meta=(DisplayName="Input Mapping Context"))
	TObjectPtr<UInputMappingContext> InputMappingContext;

	UPROPERTY(EditDefaultsOnly, meta = (DisplayName = "Input Action Map"))
	TMap<EGeneralInputAction, UInputAction*> InputActionMap;
};

USTRUCT(Blueprintable)
struct FCombatInputMapping
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, meta = (DisplayName = "Input Mapping Context"))
	TObjectPtr<UInputMappingContext> InputMappingContext;

	UPROPERTY(EditDefaultsOnly, meta = (DisplayName = "Input Action Map"))
	TMap<ECombatInputAction, UInputAction*> InputActionMap;
};