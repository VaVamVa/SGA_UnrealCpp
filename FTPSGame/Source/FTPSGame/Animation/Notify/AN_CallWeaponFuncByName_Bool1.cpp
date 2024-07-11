// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/Notify/AN_CallWeaponFuncByName_Bool1.h"
#include "Actor/Character/BaseCharacter.h"
#include "Actor/Weapon/BaseWeapon.h"

DEFINE_LOG_CATEGORY(CallWeaponFuncByName_Bool1_Log)

FString UAN_CallWeaponFuncByName_Bool1::GetNotifyName_Implementation() const
{
	if (FunctionName != "None")
		return "Call " + FunctionName;
	return "Call Weapon Func By Name";
}

void UAN_CallWeaponFuncByName_Bool1::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventRef)
{
	Super::Notify(MeshComp, Animation, EventRef);

	ABaseWeapon* Weapon = Weapon = Cast<ABaseWeapon>(MeshComp->GetOwner());
	if (Weapon == nullptr)
		Weapon = Cast<ABaseCharacter>(MeshComp->GetOwner())->GetEquippedWeapon();

	if (Weapon->IsValidLowLevelFast())
	{
		if (UFunction* Func = Weapon->FindFunction(FName(FunctionName)))
		{
			Weapon->ProcessEvent(Func, &bParam);
		}
		else
		{
			FString LogText = "Cant Find " + FunctionName + ". Check Notify Function Name";
			UE_LOG(CallWeaponFuncByName_Bool1_Log, Warning, TEXT("%s"), *LogText);
		}
	}
}
