#pragma once
#include "CoreMinimal.h"

#include "EquipmentEnum.h"

#include "EquipmentStruct.generated.h"  // generated 와 선언부 사이에 어떤 include 도 있어선 안됨.

USTRUCT(Blueprintable)
struct FEquipmentMeshAsset : public FTableRowBase // UE Data table을 이용하기 위한 상속.
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, meta=(DisplayName="Equipment Type"))
	EEquipmentType EquipmentType;

	UPROPERTY(EditDefaultsOnly, meta = (DisplayName = "Skeletal Mesh"))
	TArray<USkeletalMesh*> SkeletalMesh;
};
