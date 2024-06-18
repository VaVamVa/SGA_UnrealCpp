// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/Notify/AN_CallCharFuncByName.h"

#include "Actor/Character/BaseCharacter.h"

DEFINE_LOG_CATEGORY(CallCharFuncByNameLog)


FString UAN_CallCharFuncByName::GetNotifyName_Implementation() const
{
	if (FunctionName != "None")
		return "Call " + FunctionName;

	return "CallCharFuncByName";
}

void UAN_CallCharFuncByName::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventRef)
{
	Super::Notify(MeshComp, Animation, EventRef);

	if (ABaseCharacter* Character = Cast<ABaseCharacter>(MeshComp->GetOwner()))
	{
		if (UFunction* Function = Character->FindFunction(FName(FunctionName)))
		{
			Character->ProcessEvent(Function, nullptr);
		}
		else
		{
			FString LogText = "Cant Find " + FunctionName + ". Check Notify Function Name";
			UE_LOG(CallCharFuncByNameLog, Warning, TEXT("%s"), *LogText);
		}
	}
}

