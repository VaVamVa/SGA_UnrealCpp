240701

## 1. 관련 파일명

- [BT_DOCS](https://docs.unrealengine.com/4.27/ko/InteractiveExperiences/ArtificialIntelligence/BehaviorTrees/)

## 2. 사용되는 개념

1. Behavior Tree
2. Behavior Tree Node : `UBTNode` class. 작업, 논리 흐름 제어, 데이터 업데이트를 통한 동작 트리의 주요 작업 수행
    1. Root Node : Behavior Tree가 실행되는 시작점. 이곳에서 Blackboard Asset 설정 가능하다.
    2. Composite Node : Branch가 실행되는 기본 규칙 정의
        1. Selector
        2. Sequence
        3. Simple Parallel
    3. Task Node : Behavior Tree의 leaf node로서, 실행할 일(동작)을 정의한다.
    4. Decorator Node : 조건에 대해 관리하며, 다른 Node에 첨부되어 해당 Branch 혹은 Single Node의 실행 여부 및 시점을 결정할 수 있다.
    5. Service Node : Composite Node에 첨부되며, Branch가 실행되는 한 정의된 (`Interval`, `RandomDeviation`) 빈도로 실행된다.<br>
        체크 및 데이터 갱신에 사용된다.
        - 이들은 전통적인 Parallel 노드를 대체한다.

## 3. 선행 작업

1. `Game/Source/Game/GameBuild.cs`에 존재하는 ModuleRules 클래스의 변수 `PublicDependencyModuleNames`에 `"AIModule"`을 추가해준다.
2. `AAIController`를 상속받는 Controller를 하나 생성
3. 해당 Contorller를 AI가 적용될 Actor에 할당
4. Controller에 Behavior Tree(`UBehaviorTree`) 포인터 변수를 선언한 뒤, Blueprint BT Asset을 이 변수에 할당
5. `BeginPlay` 혹은 `OnPossess` 단계에서 `RunBehaviorTree` 함수 실행

## 4. 추가 

### 1. Data 관리

1. Behavior Tree Node는 공유 객체로 존재하여, 동일한 Behavior Tree를 이용하는 Agent(OwnerController의 Character)가 단일 노드 인스턴스를 공유한다.

2. `1`의 경우 데이터 사용량을 줄여 효율적인 실행이 가능케 해주지만, Agent 별 별개의 데이터 이용을 막아버린다.

3. 이를 해결하기 위한 3가지 방법이 존재한다

#### 1. 노드 인스턴싱

Node의 `bCreateNodeInstance` 변수를 `true`로 설정하면 각 Agent마다 고유 노드 인스턴스를 부여하여 메모리 사용량을 희생하여 각 Agent의 데이터를 안전하게 저장할 수 있다.

#### 2. Blackboard에 저장

같은 Behavior Tree를 사용하는 각 Agent들은 별개의 Blackboard 인스턴스가 할당되어 있다는 점을 이용, Blackboard Key를 Patch하며 사용하면 된다.
Blackboard는 `bool` , `float` , `FVector` , `int32` , `enum` (`uint8`) 및 `UObject*` 유형의 변수를 지원한다.

#### 3. Behavior Tree Node에 저장

노드의 메모리 내부에 변수를 사용자 정의 구조체나 클래스를 만들어 저장한다.<br>
그러나 이 메모리는 UObject 생태계의 일부가 아니며 UE4의 리플렉션 시스템의 일부가 아니며 가비지 컬렉션이 볼 수 없다. 이 때문에 UPROPERTY 지원을 사용할 수 없으며, 필요한 `UObject` 포인터를 `TWeakObjectPtr`으로 저장하는 것이 좋다.

- 예시 코드 (`BTTask_MoteTo.h`)

### 2. 감지 컴포넌트 (Perception Component)

1. Agent가 게임 월드 내 환경들을 감지(인지)하게 해주는 기능들을 모아둔 컴포넌트로서, `ActorComponent`형태로 존재하는 `UAIPerceptionComponent` 클래스 형태로 존재한다.

2. 우리가 만든 Controller Actor에서 UObject 메서드 `CreateDefaultSubobject`를 사용하여 생성 및 할당해준다.
    - Perception Component의 경우 `AAIContoroller`가 이미 가지고 있는 변수이다. <br>
    다만 전방선언만 되어있기 때문에 Perception 하위의 PerceptionComponent를 include 해주어야 한다.

3. `UAISenseConfig`는 Perceptiond에서 쓰이는 감각의 종류들을 정의하는 클래스이다. 
    - Sight, Hearing, Damagae, , Team, Touch, Prediction

4. 위의 감각들 중 필요한 감각들을 include 한 뒤 `CreateDefaultSubobject`를 사용하여 생성한 후 Preception Component의 메서드 `ConfigureSense`에 레퍼런스 형태로 전달한다.

- 만약 동적으로 Sense를 바꿔주고 싶다면, 이들을 포인터 변수 형태로 가지고 설정값들을 바꿔주는 것도 해볼만한 일일 것이다.