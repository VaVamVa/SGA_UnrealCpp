240618

## 1. 관련 파일명
- [AN_CallCharFuncByName](./FTPSGame/Source/FTPSGame/Animation/Notify/AN_CallCharFuncByName.cpp)
- AnimNotify

## 2. 사용되는 개념
- Implementation : Blueprint와 Cpp 둘 다 사용되는 함수의 경우 Generated Body에서 원본 클래스의 함수 어미에 `_Implementation`를 추가하여 선언해준다.<br>
Cpp 정의부에서는 이를 이용하여 함수를 Override 해주어야 한다.<br>
원본의 함수에 경우 Blueprint에서 사용하게 된다.<br>
`BlueprintNativeEvent`인 함수를 Override한 경우, Blueprint에서 해당 함수(Event)를 호출했을 경우 Implementation 메서드는 호출되지 않는다. [Docs_GameplayArchitecture_함수지정자]()

- FindFunction : 선언한 함수의 이름(`FName`)에 따라 함수 포인터를 연결해주는 AActor의 기본 함수. 매우 요긴하게 사용 가능할 것으로 보인다.
    - 이와 연계하여 Actor의 ProcessEvent를 활용, Delegate처럼 이용한다.

## 3. 방법
1. AnimNotify를 상속받는 class를 생성
2. Super의 `GetNotifyName` (BlueprintNative Property이므로 Implementation을 어미에 추가)을 똑같이 선언
3. Super의 `Notify`를 Override하여, Notify Call 되면 수행할 명령들 작업
4. Notify Call 시 Base Character의 함수를 이름 형태로 찾고, 존재할 경우 수행되게 함.

## 4. 추가

- Parameter가 필요하면, 멤버 변수 및 Dynamic용 Struct를 만들어서 주소값을 전달하면 된다.
    - [AN_CallCharFuncByName_Bool1](./FTPSGame/Source/FTPSGame/Animation/Notify/AN_CallCharFuncByName_Bool1.cpp)
    - [Montage_that_uses_thisNotify](./FTPSGame/Content/Animation/Montages/Reloading/)