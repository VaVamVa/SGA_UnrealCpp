240701

## 1. 관련 파일명


## 2. 사용되는 개념

1. Make Notify In Anim Blueprint
2. Conduit

## 3. 방법

1. Animation Blueprint 내에 Anim Graph에서
2. 원하는 트랜지션 선택하면 Detail 부분에서 애니메이션 시작, 중단, 마무리 시 수행할 이벤트 이름을 적는 곳에 의미를 나타내는 이름을 적는다.
3. Event Graph에서 해당 이름을 적어보면, AnimNotify이 생성된 것을 확인할 수 있고, Eevent로 호출하여 수행할 노드들을 배치하면 된다.

1. Conduit 내부의 Transition은 자동으로 넘어가게 두고, Conduit에 진입, 진행되는 Transition들에 조건을 추가해준다.
2. Alias와 적절히 조합하여 Animation node들을 배치하면 훨씬 정갈한 Graph를 짤 수 있다.


## 4. 추가 