// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_GimicClear.h"
#include "BaseEliteMonster.h"
#include "AIController.h"
#include <Blueprint/AIBlueprintHelperLibrary.h>
#include "BehaviorTree/BlackboardComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"

UBTTask_GimicClear::UBTTask_GimicClear(FObjectInitializer const& ObjectInitializer)
{
	NodeName = TEXT("Gimic Clear");
}

EBTNodeResult::Type UBTTask_GimicClear::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//Cast to Elite Monster
	auto const* const cont = OwnerComp.GetAIOwner();
	auto* const EliteMonster = Cast<ABaseEliteMonster>(cont->GetPawn());

	//off Shield Effect
	EliteMonster->GetSpecificEffect()->Deactivate();
	EliteMonster->ReSetTimer();
	EliteMonster->SetInvincible(false);

	//clear Gimic, so Monster Can Take Damage now
	UAIBlueprintHelperLibrary::GetAIController(EliteMonster)->GetBlackboardComponent()->SetValueAsBool("CanTakeDamage", true);

	return EBTNodeResult::Succeeded;
}
