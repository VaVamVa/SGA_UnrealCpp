// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AN_CallCharFuncByName.generated.h"

/**
 * 
 */

DECLARE_LOG_CATEGORY_EXTERN(CallCharFuncByNameLog, Log, All)

UCLASS()
class FTPSGAME_API UAN_CallCharFuncByName : public UAnimNotify
{
	GENERATED_BODY()

	UPROPERTY(EditInstanceOnly, meta = (AllowPrivateAccess = true)) // 이 하나의 클래스로 여러 노티파이의 역할을 해줄 것이기에, Instance 기준으로.
	FString FunctionName = "None";

	// Blueprint에서도 사용 가능한 함수의 경우에 Implementation 이 붙어있어야 C++에서 Override가 가능하다.
	// Generated body로 Engine에 적용될 때 해당 함수가 만들어진다.
	FString GetNotifyName_Implementation() const;  

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventRef) override;

	
};
