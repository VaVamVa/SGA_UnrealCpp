// Copyright Epic Games, Inc. All Rights Reserved.

#include "FTPSGameGameMode.h"
#include "FTPSGameCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Widgets/PlayerHUD.h"

AFTPSGameGameMode::AFTPSGameGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Characters/Hero/BP_Hero"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	HUDClass = APlayerHUD::StaticClass();
}
