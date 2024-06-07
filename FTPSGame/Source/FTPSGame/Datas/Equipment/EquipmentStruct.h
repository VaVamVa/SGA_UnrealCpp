#pragma once
#include "CoreMinimal.h"

#include "EquipmentEnum.h"

#include "EquipmentStruct.generated.h"  // generated �� ����� ���̿� � include �� �־ �ȵ�.

USTRUCT(Blueprintable)
struct FEquipmentMeshAsset : public FTableRowBase // UE Data table�� �̿��ϱ� ���� ���.
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, meta=(DisplayName="Equipment Type"))
	EEquipmentType EquipmentType;

	UPROPERTY(EditDefaultsOnly, meta = (DisplayName = "Skeletal Mesh"))
	TArray<USkeletalMesh*> SkeletalMesh;
};
