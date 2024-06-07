// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Datas/Character/InputStruct.h"

#include "DA_InputMappingDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class FTPSGAME_API UDA_InputMappingDataAsset : public UDataAsset
{
	GENERATED_BODY()
	

public:
	UPROPERTY(EditDefaultsOnly, Category = Input, meta = (AllowPrivateAccess = true))
	FGeneralInputMapping GeneralInputMapping;

	UPROPERTY(EditDefaultsOnly, Category = Input, meta = (AllowPrivateAccess = true))
	FCombatInputMapping CombatInputMapping;

};
