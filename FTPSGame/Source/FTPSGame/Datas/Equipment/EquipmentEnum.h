#pragma once
#include "CoreMinimal.h"

UENUM(Blueprintable)
enum class EEquipmentType : uint8
{
	// UE Meta ÁöÁ¤ÀÚ
	None UMETA(Hidden),
	Equipment_Head UMETA(DisplayName = "Head"),
	Equipment_Body UMETA(DisplayName = "Body"),
	Equipment_ExoLegs UMETA(DisplayName = "ExoLegs"),
	Equipment_Laptop UMETA(DisplayName = "Laptop"),
	Equipment_LeftBag UMETA(DisplayName = "LeftBag"),
	Equipment_RightBag UMETA(DisplayName = "RightBag"),
	Equipment_ChestBag UMETA(DisplayName = "ChestBag"),
	Equipment_LeftGranade UMETA(DisplayName = "LeftGranade"),
	Equipment_RightGranade UMETA(DisplayName = "RightGranade")


};
