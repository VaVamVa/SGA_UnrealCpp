## Actor Spawner 구현하기

1. 특정 액터가 어디에 구현되어 있는지 모를때.
    - 해당 액터의 원본 이름은 에디터에서 확인 가능하고, 이를 Document에서 검색하면 include 경로를 알 수 있다.

2. Base Class에 기반하여 자손 클래스를 런타임 중에 결정하고 싶을 때<br>
    ```
    UPROPERTY(EditDefaultOnly, meta=(AllowPrivateAccess="true"))
    TSubclassOf(ABaseClass) VarName;
    ```
    - `ABaseClass`를 상속받는 클래스를 에디터에서 정해서 스폰 액터 시킬 수 있다.

3. Timer 만들기
KismetLibrary에서 SetTimer

4. Static Mesh와 Material Setting하기


## 과제
1. 3초마다 구 한개씩 스폰 (최대 30개)
2. 어느 한 점 기준으로 공전시키기
3. 색깔 주기적으로 바꾸기

- 추가과제
    1. 공전 하며 위 아래로 움직이게 하기
    2. 캐릭터 중심으로 공전시키기
    3. 일정 기준에 맞춰 순차적 스폰시키기