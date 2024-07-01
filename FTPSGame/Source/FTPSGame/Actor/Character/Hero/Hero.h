#pragma once

#include "CoreMinimal.h"
#include "Actor/Character/BaseCharacter.h"

class USpringArmComponent;
class UCameraComponent;

class UDA_InputMappingDataAsset;
class UEnhancedInputComponent;
struct FInputActionValue;
#include "Datas/Character/InputStruct.h"

#include "Hero.generated.h"
/**
 * 
 */
UCLASS()
class FTPSGAME_API AHero : public ABaseCharacter
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleDefaultsOnly, meta=(AllowPrivateAccess=true))
	TObjectPtr<USpringArmComponent> SpringArm;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(AllowPrivateAccess=true))
	TObjectPtr<UCameraComponent> Camera;

	UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess=true))
	TObjectPtr<UDA_InputMappingDataAsset> InputDataAsset;

	
public:
	AHero();

	virtual void Tick(float DeltaSecond) override;

	FORCEINLINE UCameraComponent* GetCamera() const { return Camera; }

protected:
	virtual void BeginPlay() override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void SetGeneralInputMapping(UEnhancedInputComponent* EnhancedPlayerInputComponent);
	void SetCombatInputMapping(UEnhancedInputComponent* PlayerInputComponent);

	void Move(const FInputActionValue& Value);
	void View(const FInputActionValue& Value);
};
