#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

class UTextBlock;

#include "AmmoInfo.generated.h"

/**
 * Max Ammo
 * Current Ammo
 * 
 * need to update with BaseWeapon
 */
UCLASS()
class FTPSGAME_API UAmmoInfo : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	TObjectPtr<UTextBlock> AmmoText;

	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	TObjectPtr<UTextBlock> MagazineText;
	
public:
	UFUNCTION()
	void Update(int32 Ammo, int32 Magazine);
	void UpdatePosition(FVector2D NewPosition);
};
