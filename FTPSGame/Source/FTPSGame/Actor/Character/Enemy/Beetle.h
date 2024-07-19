// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/Character/Enemy/BaseEnemy.h"
#include "Beetle.generated.h"

/**
 * 
 */
UCLASS()
class FTPSGAME_API ABeetle : public ABaseEnemy
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(AllowPrivateAccess=true))
	bool bMove;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(AllowPrivateAccess=true))
	bool bAttacking;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(AllowPrivateAccess=true))
	bool bCheckOpponent;

public:
	ABeetle();


protected:
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	void OnTimer();
	FTimerHandle MyTimer;
	int32 TimerCount;
};
