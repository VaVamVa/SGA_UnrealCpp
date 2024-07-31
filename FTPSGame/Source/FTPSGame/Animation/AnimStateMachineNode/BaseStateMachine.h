// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimGraphNode_StateMachine.h"
#include "BaseStateMachine.generated.h"

/**
 * 
 */
UCLASS()
class FTPSGAME_API UBaseStateMachine : public UAnimGraphNode_StateMachine
{
	GENERATED_BODY()

public:
	UBaseStateMachine();

	virtual FLinearColor GetNodeTitleColor() const override;
	virtual FText GetTooltipText() const override;
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
};
