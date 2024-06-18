#include "Actor/Character/Hero/Hero.h"

#include "Utilities/Helper.h"
#include "Datas/Input/DA_InputMappingDataAsset.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

#include "GameFramework/CharacterMovementComponent.h"


AHero::AHero()
{
	SpringArm = Helper::CreateSceneComponent<USpringArmComponent>(this, "Camera Arm", GetMesh());
	Camera = Helper::CreateSceneComponent<UCameraComponent>(this, "Camera", SpringArm);

	SpringArm->SetRelativeRotation(FRotator(0.0, 90.0, 0.0));
	SpringArm->SetRelativeLocation(FVector(0.0, 0.0, 150.0));
	
	SpringArm->bUsePawnControlRotation = true;
	bUseControllerRotationYaw = false;

	UCharacterMovementComponent* MovementComponent = GetCharacterMovement();
	//MovementComponent->bOrientRotationToMovement = true;
	MovementComponent->bOrientRotationToMovement = false;
	MovementComponent->bUseSeparateBrakingFriction = true;
	
	// 컨트롤러 선호 회전 사용
	MovementComponent->bUseControllerDesiredRotation = true;
	MovementComponent->RotationRate = FRotator(0, 180, 0);

	InputDataAsset = Helper::GetAssetFromConstructor<UDA_InputMappingDataAsset>("/Script/FTPSGame.DA_InputMappingDataAsset'/Game/Characters/Hero/Input/DA_InputDataAsset.DA_InputDataAsset'");

}

void AHero::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		if (Subsystem)
		{
			//GEngine->AddOnScreenDebugMessage(1, 3.0f, FColor::Blue, "Subsystem");

			if (InputDataAsset->GeneralInputMapping.InputMappingContext)
				Subsystem->AddMappingContext(InputDataAsset->GeneralInputMapping.InputMappingContext, 0);
			if (InputDataAsset->CombatInputMapping.InputMappingContext)
				Subsystem->AddMappingContext(InputDataAsset->CombatInputMapping.InputMappingContext, 0);
		}
	}
}


#pragma region InputMapping

void AHero::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedPlayerInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (!EnhancedPlayerInputComponent) return;

	//GEngine->AddOnScreenDebugMessage(2, 3.0f, FColor::Blue, "Setting Input Mapping Context");

	SetGeneralInputMapping(EnhancedPlayerInputComponent);
	SetCombatInputMapping(EnhancedPlayerInputComponent);
}

void AHero::SetGeneralInputMapping(UEnhancedInputComponent* EnhancedPlayerInputComponent)
{
	UInputAction* Action = *InputDataAsset->GeneralInputMapping.InputActionMap.Find(EGeneralInputAction::Move);
	if (Action)
		EnhancedPlayerInputComponent->BindAction(Action, ETriggerEvent::Triggered, this, &AHero::Move);

	Action = *InputDataAsset->GeneralInputMapping.InputActionMap.Find(EGeneralInputAction::View);
	if (Action)
		EnhancedPlayerInputComponent->BindAction(Action, ETriggerEvent::Triggered, this, &AHero::View);
}

void AHero::SetCombatInputMapping(UEnhancedInputComponent* EnhancedPlayerInputComponent)
{
	UInputAction* Action = *InputDataAsset->CombatInputMapping.InputActionMap.Find(ECombatInputAction::Interact);

	if (Action)
		EnhancedPlayerInputComponent->BindAction(Action, ETriggerEvent::Triggered, this, &ABaseCharacter::Interact);

	Action = *InputDataAsset->CombatInputMapping.InputActionMap.Find(ECombatInputAction::MainSlot);
	if (Action)
		EnhancedPlayerInputComponent->BindAction(Action, ETriggerEvent::Triggered, this, &ABaseCharacter::SwapMainSlotWeapon);
	
	Action = *InputDataAsset->CombatInputMapping.InputActionMap.Find(ECombatInputAction::SubSlot);
	if (Action)
		EnhancedPlayerInputComponent->BindAction(Action, ETriggerEvent::Triggered, this, &ABaseCharacter::SwapSubSlotWeapon);

	Action = *InputDataAsset->CombatInputMapping.InputActionMap.Find(ECombatInputAction::Aim);
	if (Action)
	{
		EnhancedPlayerInputComponent->BindAction(Action, ETriggerEvent::Ongoing, this, &ABaseCharacter::StartAiming);
		EnhancedPlayerInputComponent->BindAction(Action, ETriggerEvent::Triggered, this, &ABaseCharacter::EndAiming);
	}
}

void AHero::Move(const FInputActionValue& Value)
{
	FVector2D InputValue = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		//GEngine->AddOnScreenDebugMessage(3, 3.0f, FColor::Blue, "Set Movement input");

		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector ForwardVector = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightVector = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(ForwardVector, InputValue.Y);
		AddMovementInput(RightVector, InputValue.X);

	}
}

void AHero::View(const FInputActionValue& Value)
{
	FVector2D InputValue = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		//GEngine->AddOnScreenDebugMessage(4, 3.0f, FColor::Blue, "Set Controller yaw input");

		AddControllerYawInput(InputValue.X);
		AddControllerPitchInput(InputValue.Y);
	}
	
}

#pragma endregion InputMapping