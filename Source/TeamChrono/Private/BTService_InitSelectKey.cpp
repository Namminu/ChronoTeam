// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_InitSelectKey.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_InitSelectKey::UBTService_InitSelectKey()
{
	NodeName = TEXT("Init Selected Key");
}

void UBTService_InitSelectKey::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(), SelectBool);
}
