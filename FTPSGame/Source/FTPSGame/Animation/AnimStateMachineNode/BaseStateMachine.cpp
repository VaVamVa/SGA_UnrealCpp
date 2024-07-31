// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimStateMachineNode/BaseStateMachine.h"

UBaseStateMachine::UBaseStateMachine()
{
}

FLinearColor UBaseStateMachine::GetNodeTitleColor() const
{
	return FLinearColor(0.1f, 0.5f, 0.8f);
}

FText UBaseStateMachine::GetTooltipText() const
{
	return FText::FromString(TEXT("This is a custom State Machine node."));
}

FText UBaseStateMachine::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return FText::FromString(TEXT("Base State Machine"));
}
