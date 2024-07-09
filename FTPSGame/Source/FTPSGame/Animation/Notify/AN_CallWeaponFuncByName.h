// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AN_CallWeaponFuncByName.generated.h"

/**
 * 
 */
DECLARE_LOG_CATEGORY_EXTERN(CallWeaponFuncByNameLog, Log, All)

UCLASS()
class FTPSGAME_API UAN_CallWeaponFuncByName : public UAnimNotify
{
	GENERATED_BODY()
	
	UPROPERTY(EditInstanceOnly, meta=(AllowPrivateAccess = true))
	FString FunctionName = "None";

	FString GetNotifyName_Implementation() const override;

	void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventRef) override;
};
