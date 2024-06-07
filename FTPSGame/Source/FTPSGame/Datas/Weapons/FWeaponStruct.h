#pragma once

#include "CoreMinimal.h"

#include "EWeaponEnum.h"

#include "FWeaponStruct.generated.h"

USTRUCT(Blueprintable)
struct FWeaponMeshAssetTable : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, meta=(DisplayName="Weapon Name"))
	EWeaponName WeaponName;

	UPROPERTY(EditDefaultsOnly, meta = (DisplayName = "Skeletal Mesh"))
	USkeletalMesh* SkeletalMesh;

	UPROPERTY(EditDefaultsOnly, meta = (DisplayName = "Skins"))
	UMaterialInstance* Skins[4];
};
