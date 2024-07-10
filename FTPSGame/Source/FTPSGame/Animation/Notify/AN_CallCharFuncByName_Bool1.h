// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AN_CallCharFuncByName_Bool1.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(CallCharFuncByName_Bool1_Log, Log, All)


/**
 * 
 */
UCLASS()
class FTPSGAME_API UAN_CallCharFuncByName_Bool1 : public UAnimNotify
{
	GENERATED_BODY()
	
	UPROPERTY(EditInstanceOnly, meta = (AllowPrivateAccess = true))
	FString FunctionName = "None";

	FString GetNotifyName_Implementation() const;

	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
	bool bParam;

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventRef) override;
};
