240618

## 1. 관련 파일명
- [AnimSeq_for_AimOffset](./FTPSGame/Content/Animation/Rifle/Aim)
- [AimOffset](./FTPSGame/Content/Animation/AimOffset)
- [AnimCpp](./FTPSGame/Source/FTPSGame/Animation/Character_AnimInstance)
- [AnimBlueprint](./FTPSGame/Content/Animation/AnimInstance)

## 2. 사용되는 개념

- Additive Anim
- Aim Offset File
- NormalizedDeltaRotator

## 3. 방법

1. Blueprint : Additive Setting Of Anim Seq's At Property Matrix
    1. Aim Offset에 사용할 Anim Seq들을 모두 선택하여 `Asset action-Edit at Property matrix`로 Asset 대량 편집 창을 열고, Details에서 편집한다.
    2. Additive Anim Type : ?? `Mesh Space`로 설정해준다.
    3. Base Pose Type : ?? `Selected animation frame`으로 설정해준다.
    4. Base Pose Animation : Additive Setting의 경우 Base Pose 에서 Adiitve Pose를 "더하여" Pose를 Update하기 때문에, 통상의 포즈(Idle Pose)를 Base Pose Animation으로 설정하여준다.<br>
    그러면 통상 포즈에 해당 Anim Sequence를 더하여 자연스러운 Animation을 만들어 주는 것 같다. (?)

2. Blueprint : Create Aim Offset Asset File
    1. `우클릭 - Animation - AimOffset`으로 AimOffset 파일을 생성한다.
    2. 가로축 Yaw, 세로축 Pitch로 가로 세로로 바라볼 각도 한계를 설정해준다.
    3. 앞서서 미리 세팅해둔 AnimSeq들을 Aim 각도에 따라 적절히 배치해준다.

3. Apply Aim Offset In Anim Instance
    1. 현재 사용하고 있는 Anim Instance에서 Aim Offset을 적용할 Animation Asset이 위치한 그래프로 이동한다.
    2. Aim Offset을 에셋 브라우저에서 드래그 앤 드랍으로 설정하고, Base Pose에 적용할 Pose를 연결해준다.
    3. 이때 Yaw와 Pitch는 `UKismetMathLibrary::NormalizedDeltaRotator(A=Controller Rotation, B=TargetActorRotation)`으로 A - B의 정규화한 값에서 Yaw Pitch를 얻어내 사용한다.
        - Blueprint의 경우 `Delta(Rotator)` 이란 함수로 존재한다.
    4. 그 결과값을 Output Animation Pose 에 연결, 혹은 추후 이용될 곳으로 연결하여 마무리한다.


## 4. 추가 - 카메라 이동 및 Fov 값 조정을 통한 Aim

1. Blueprint에서 Timeline 노드를 생성하여 내부에 Float Curve로 Fov, Camera_Y_Location 트랙을 만들어 준다.
    - 트랙의 동작 시간은 임의로 정한다 (Ex-0.5s)
2. Fov : 원래의 Fov값을 `Camera-Detail-Setting`에서 확인하여 초기값으로 설정, 트랙의 마무리에 결과 Fov값을 넣어준다.
3. Camera Y Location : Relative Location이므로, 초기값은 0, 결과값은 이동 완료된 카메라 위치를 설정해준다.
    - 임의의 카메라를 하나 더 만들어 직접 이동시켜보면서 값을 확인했다.
4. Aim Input 입력 시 `Time Line-Play`, Aim Input 해제 시 `Time Line-Reverse`를 트리거 시켜주었고, 해당 결과값 중 Fov값은 Camera의 `Set Field Of View`로 전달하고, Location_Y는 `Set Relative Location`으로 Y에 전달해 주었다.
    - `Get Relative Location`으로 X, Z 값은 유지