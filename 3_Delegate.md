240522

# Delegate

## 1. 관련 파일명
- [BaseWeapon.h](./FTPSGame/Source/FTPSGame/Actor/Weapon/BaseWeapon.h) -> Delegate 신호 받는 객체
- [AmmoInfo.cpp](./FTPSGame/Source/FTPSGame/Widgets/AmmoInfo/AmmoInfo.cpp) -> Delegate로 실행할 함수 존재
- [Hero.cpp](./FTPSGame/Source/FTPSGame/Actor/Character/Hero/Hero.cpp) -> Delegate에 신호 전달할 객체

## 2. 사용되는 개념

- [Delegate](https://docs.unrealengine.com/4.27/ko/ProgrammingAndScripting/ProgrammingWithCPP/UnrealArchitecture/Delegates/)
    - DECLARE_MULTICAST_DELEGATE...
    - DECLARE_DYNAMIC_DELEGATE...
    - DECLARE_DYNAMIC_MULTICAST_DELEGATE...
    - DECLARE_DYNAMIC_DELEGATE...
    - DECLARE_DYNAMIC_MULTICAST_DELEGATE...
- AddDynamic
    - "Helper macro to bind a UObject instance and a member UFUNCTION to a dynamic multi-cast delegate."

## 3. 방법

1. 필요 조건 (사용방식에 따른 Delegate 종류 설정) <br>
    이번의 경우엔 `MyClass(BaseWeapon)`가 신호 수용, Delegate `DelegateName(FAmmoUpdate)`에 신호를 전달하여 Bind된 함수(`UFUNCTION(Update)`)을 실행한다.
    - 또한, 신호 감지에 따라 실행될 함수가 한 개 이기 때문에, `MultiCast`를 사용할 필요가 없다.
    - 또한, Editor에서 해당 Delegate Event를 호출할 필요가 없기 때문에, `Dynamic`을 사용할 필요가 없다.

2. 선언부에서 Delegate 선언 (`BaseWeapon`의 헤더파일에서 확인 가능) <br>
    ```
    ...
    #include "MyClass.generated.h"

    DECLARE_DELEGATE_TwoParams(FDelegateType, int32, int32);

    class MyClass
    {
        ...
    public:
        FDelegateType DelegateName;

        ...
    };
    ```
    - `Dynamic`이라면 Delegate 선언 시 Editor에서 표현할 `Pin 변수명` 도 같이 기입해야 한다.
        ```
        DECLARE_DYNAMIC_DELEGATE_TwoParams(FDelegateType, int32, Param_1, int32, Param_2);
        ```
    
- 아래의 `3~4`는 `BaseWeapon::BindAmmoUpdateDelegate(AHero* Player)`에서 확인 가능

3. 구현부에서 Delegate에 `BindUFunction`을 이용하여 Bind될 함수명(`String`)을 전달<br>
    ```
    DelegateName.BindUFunction(Object, "UFuncName");
    ``` 
    - `MultiCast`라면 `AddDynamic`을 이용하여 함수명이 아닌 함수 포인터로 전달<br>
        ```
        DelegateName.AddDynamic(Object, &Object::UFunc);
        ``` 

4. 다른 객체에서 `DelegateName`을 이용해 Bind된 함수를 실행하도록 할 수 있다.<br>
    ```
    if ((MyClassInstance->DelegateName).IsBound())
        (MyClassInstance->DelegateName).Execute(Param_1, Param_2);
    ```
    - 만약 `MultiCast`라면 여러가지 객체의 함수들이 담겨있을 수 있기에, `Broadcast`를 사용한다.
        ```
        if ((MyClassInstance->DelegateName).IsBound())
            (MyClassInstance->DelegateName).Broadcast(Param_1, Param_2);
        ```

## 4. 추가

- 위의 예시파일 `BaseWeapon`의 경우, 자기 자신의 함수를 Delegate에 연결하는 것이 아닌, 외부의 객체(`AmmoInfo`_UserWidget)에 존재하는 함수를 Bind하여 이용하고 있다.
    - 이런 방식도 가능하다.

1. 어디서 신호를 받을 것인가. (`DECLARE_DELEGATE`)
    - Editor에서도 이용할 것인가? (`DYNAMIC_`)
    - 여러 함수를 Bind할 것인가? (`MULTICAST_`)
    - 몇 개의 매개변수가 필요한가? (`_NsParams`)
    1. 첫 번째 매개변수 : 이용할 Delegate 자료형
    2. (`Parmas` 존재 시,) 두 번째 이후 매개변수 : "only 자료형"(`DEFAULT`) / "자료형, 변수명" (`DYNAMIC`)

2. (어디의,) 무슨 함수를 실행할 것인가. 
    - 메서드 : `BindUFunction`(`DEFAULT`) / `AddDynamic`(`MULTICAST`)
    - 첫 번째 매개변수 : Object
    - 두 번째 매개변수 : 바인딩될 함수 "이름"(`DEFAULT`) / "포인터"(`MULTICAST`)

3. 어느 곳에서 신호기를 누를 것인가. 
    - 메서드 : `Execute`(`DEFAULT`) / `Broadcast`(`MULTICAST`)
        - 하나의 함수만 실행하기에 Execute / 여러 함수에 뿌려야하기 때문에 Broadcast
    - `Parmas`에 따라 매개변수 전달.