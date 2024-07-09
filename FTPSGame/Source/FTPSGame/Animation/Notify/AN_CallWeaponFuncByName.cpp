// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/Notify/AN_CallWeaponFuncByName.h"

#include "Actor/Weapon/BaseWeapon.h"

DEFINE_LOG_CATEGORY(CallWeaponFuncByNameLog)

FString UAN_CallWeaponFuncByName::GetNotifyName_Implementation() const
{
	if (FunctionName != "None")
		return "Call " + FunctionName;
	return "Call Weapon Func By Name";
}

void UAN_CallWeaponFuncByName::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventRef)
{
	Super::Notify(MeshComp, Animation, EventRef);

	if (ABaseWeapon* Weapon = Cast<ABaseWeapon>(MeshComp->GetOwner()))
	{
		if (UFunction* Func = Weapon->FindFunction(FName(FunctionName)))
		{
			Weapon->ProcessEvent(Func, nullptr);
		}
		else
		{
			FString LogText = "Cant Find " + FunctionName + ". Check Notify Function Name";
			UE_LOG(CallWeaponFuncByNameLog, Warning, TEXT("%s"), *LogText);
		}
	}
}
