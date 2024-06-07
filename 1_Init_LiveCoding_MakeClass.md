
## 시작 폴더

C#을 이용한 빌드 스크립트가 있다 -> 확장성을 위해

#### + 업로드용 필수 디렉토리

1. BP : Config, Content, uproject
2. Cpp : Source
    - uproject 우클릭 -> generate VS build flie -> sln 파일 생성 -> VS 빌드 후에 pjt 파일 이용 가능.
3. Plugin : Plugin
    - 플러그인 적용 했을 경우. 없는 경우도 많음. (공식파일의 경우 없음)

## 라이브 코딩 
(?)

`ctrl + alt + F11`로 라이브 코딩 빌드를 해줘야 한다. (ctrl B 불가)
라이브 코딩 쓰기 싫으면 에디터 오른쪽 아래 그래프모양 옆 점 세개 클릭 후 라이브코딩 비활성화


## Cpp을 이용하여 클래스 만들기

### 빌드 스크립트에서 추가

[Module](https://dev.epicgames.com/documentation/ko-kr/unreal-engine/setting-up-editor-modules-for-customizing-the-editor-in-unreal-engine)
pjt.module

pjt_name\Source\pjt_name\pjt_name.Build.cs에서
`PublicIncludePaths.Add(ModuleDirectory);`를 `PublicDependencyModuleNames.~~~~` 아래에 추가
- ? 이유 찾아보기.

### 새 BP Class 만들기

C++ 클래스 디렉토리
새 클래스 만들기 -> 액터
새폴더 -> 이름 후 생성

### 변수 선언

TObjectPtr<type> 혹은 type*로 포인터 변수를 선언한다.

만약 Static Mesh 컴포넌트를 추가하고 싶다면, header에서 `TObjectPtr<UStaticMeshComponent> Mesh;`를 선언,
cpp 구현부에서 `Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Static Mesh");`로 할당해 준다.
- 앞에 해당 자료형과 관련된 접두어 한 단어가 붙는다.
    - U(Class), T, A(actor), F(Structure, Delegate), E(Enum)
- Ptr 변수의 경우 GC가 해제해버릴 수 있으므로, UPROPERY Decorator를 적어주어 GC가 해제하는것을 방지할 수 있다.

### UPROPERTY

"에디터"와 "cpp에서 선언한 변수"를 연동하고 싶으면 UPROPERTY("속성")을 데코레이터로 추가해야한다.
- <b>Blueprint 통신이 가능하게 해준다.</b>
- 자매품 UFUNCTION (언젠간 할거)

- [프로퍼티 지정자](https://dev.epicgames.com/documentation/ko-kr/unreal-engine/unreal-engine-uproperties?application_version=5.3)
    1. Visible : 볼 수 만 있다
    2. Edit : 수정이 가능하다
    3. DefaultsOnly : 블프 내부에서만 수정 혹은 볼 수 있다.
    4. InstanceOnly : 월드상에서만 수정 혹은 볼 수 있다.
    5. AnyWhere : 어디에서든 사용 가능하다.
    6. BlueprintReadOnly : 블프에서 읽기(Get)만 가능
    7. BlueprintReadWrite : 블프에서 읽고 쓰기(Get, Set) 가능.
    8. Category : 블프 에디터 변수 카테고리 및 "클래스 디테일 카테고리" 등을 설정 가능하다. (디폴트 매개변수 처럼 사용)
    9. meta
    - Visible / Edit,BlueprintRead____ 동시 사용 불가능

- meta 예시
우리가 만든 클래스 변수가 private면, 이를 상속받는 클래스에서도 BluePrint에서 읽어오게 할 수 있게 해줘야 한다.
1. `meta=(AllowPrivateAcces="true")`를 UPROPERY 안에 추가해준다.
2. protected 변수로 선언해주면 된다.
3. `AnyWhere`를 사용한다.

### 외부 매크로 생성기 이용

[Macro](https://benui.ca/)
UnrealMacroGenerator.vsix를 실행하여 visualstudio 언리얼용 매크로 시스템을 받는다.
alt w : 매크로 생성
alt e : 매크로 수정


### Static Mesh Component 선언/할당하기. (Component 생성/ 구현부에서 할당)

Static Mesh UObject를 선언해주고, 생성자에서 CreateDefaultSubobject 템플릿 자료형을 이용해 할당해준다.
원래 에디터에서는 Mesh 컴포넌트에 직접 Mesh를 할당해 주었지만, 스크립트로도 가능하다.
이용하려는 메시의 레퍼런스 복사 (실제 행위는 레퍼런스 경로 복사임) 를 해준 뒤,
ConstructorHelpers의 FObejctFinder 템플릿 함수에 해당 경로를 작성하여 받아놓은 메시의 data를 해당 mesh 변수에 할당하는 것이 가능하다.


## 과제

#### 새로운 액터 만들기
1. Scene Root Component 설정
2. Static Mesh Component 설정
    1. mesh는 아무거나 설정
3. Text Render Component 설정
    1. Static Mesh 위로 설정
        - [AActor::FTransform](https://docs.unrealengine.com/4.26/en-US/API/Runtime/Core/Math/FTransform/)
        - [BoundingBox](https://dev.epicgames.com/documentation/en-us/unreal-engine/BlueprintAPI/StaticMesh/GetBoundingBox?application_version=5.4)
        - [Text Alignment](https://docs.unrealengine.com/4.27/en-US/PythonAPI/class/TextRenderComponent.html)
            - 검색어 : alignment
    2. Text = 액터 이름으로 설정
        - [UTextRenderComponent](https://docs.unrealengine.com/4.27/en-US/API/Runtime/Engine/Components/UTextRenderComponent/)
        - [FText](https://docs.unrealengine.com/4.27/en-US/API/Runtime/Core/Internationalization/FText/)


## (+) 이전에 작업한 C++ class가 사라졌을 때.

1. [관련 Blog](https://velog.io/@woolzam/%EC%96%B8%EB%A6%AC%EC%96%BC-Unreal-C-%ED%81%B4%EB%9E%98%EC%8A%A4%EA%B0%80-%EC%82%AC%EB%9D%BC%EC%A7%88-%EB%95%8C)
    1. 현재 프로젝트에서 생성된 디버깅 폴더인 `Binaries`폴더와 `Intermediate`폴더를 삭제하고 프로젝트를 실행하면 재빌드해줌.
    2. 에디터 설정에서 "시작시 강제 컴파일 실행"을 True로 바꿔줌.

2. 라이브 코딩 끄고 cpp 파일에서만 빌드하기.

