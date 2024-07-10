// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/Notify/AN_CallCharFuncByName_Bool1.h"
#include "Actor/Character/BaseCharacter.h"

DEFINE_LOG_CATEGORY(CallCharFuncByName_Bool1_Log)

FString UAN_CallCharFuncByName_Bool1::GetNotifyName_Implementation() const
{
	if (FunctionName != "None")
		return "Call " + FunctionName;

	return "CallCharFuncByName";
}

void UAN_CallCharFuncByName_Bool1::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventRef)
{
	Super::Notify(MeshComp, Animation, EventRef);

	if (ABaseCharacter* Character = Cast<ABaseCharacter>(MeshComp->GetOwner()))
	{
		if (UFunction* Function = Character->FindFunction(FName(FunctionName)))
		{
			Character->ProcessEvent(Function, &bParam);
		}
		else
		{
			FString LogText = "Cant Find " + FunctionName + ". Check Notify Function Name";
			UE_LOG(CallCharFuncByName_Bool1_Log, Warning, TEXT("%s"), *LogText);
		}
	}
}
