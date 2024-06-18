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

	UPROPERTY(EditInstanceOnly, meta = (AllowPrivateAccess = true)) // �� �ϳ��� Ŭ������ ���� ��Ƽ������ ������ ���� ���̱⿡, Instance ��������.
	FString FunctionName = "None";

	// Blueprint������ ��� ������ �Լ��� ��쿡 Implementation �� �پ��־�� C++���� Override�� �����ϴ�.
	// Generated body�� Engine�� ����� �� �ش� �Լ��� ���������.
	FString GetNotifyName_Implementation() const;  

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventRef) override;

	
};
