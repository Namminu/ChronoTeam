// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_NotTakeDamage.h"
#include "AIController.h"
#include <BaseEliteMonster.h>

UBTTask_NotTakeDamage::UBTTask_NotTakeDamage(FObjectInitializer const& ObjectInitializer)
{
	NodeName = TEXT("Not Take Damage");
}

EBTNodeResult::Type UBTTask_NotTakeDamage::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto const* const cont = OwnerComp.GetAIOwner();
	auto const EliteMonster = Cast<ABaseEliteMonster>(cont->GetPawn());

	//Set Monster to Invincible
	EliteMonster->SetInvincible(true);

	return EBTNodeResult::Succeeded;
}
