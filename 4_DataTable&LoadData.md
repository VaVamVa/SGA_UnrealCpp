240523

## 별도의 header만 존재하는 helper 소스 코드 생성 방법

1. 유틸리티 및 함수 라이브러리 등 필요한 코드들이 따로 존재하는 파일 생성
2. 새로 만든 Header에 `"CoreMinimal"` 인클루드
3. VS 모두 저장 후 종료
4. UE editor에서 tool->VS 프로젝트 새로고침

## Data Table 만들기

Enum, Struct를 이용해서 만들음

``` 
//Struct
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


//Enum
#pragma once
#include "CoreMinimal.h"

UENUM(Blueprintable)
enum class EEquipmentType : uint8
{
	// UE Meta 지정자
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

```