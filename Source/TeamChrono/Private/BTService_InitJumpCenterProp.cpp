// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_InitJumpCenterProp.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_InitJumpCenterProp::UBTService_InitJumpCenterProp()
{
	NodeName = TEXT("Init Select BB Key");
}

void UBTService_InitJumpCenterProp::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(), SelectBool);
}