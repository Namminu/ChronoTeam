// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_SetCanTakeDamage.h"
#include <Blueprint/AIBlueprintHelperLibrary.h>
#include "AIController.h"
#include <BaseEliteMonster.h>
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_SetCanTakeDamage::UBTTask_SetCanTakeDamage(FObjectInitializer const& ObjectInitializer)
{
	NodeName = TEXT("Set Can Take Damage");
}

EBTNodeResult::Type UBTTask_SetCanTakeDamage::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto const* const cont = OwnerComp.GetAIOwner();
	ABaseEliteMonster* const EliteMonster = Cast<ABaseEliteMonster>(cont->GetPawn());

	//clear Gimic, so Monster Can Take Damage now
	UAIBlueprintHelperLibrary::GetAIController(EliteMonster)->GetBlackboardComponent()->SetValueAsBool("CanTakeDamage", isCanDamage);
	return EBTNodeResult::Succeeded;
}
