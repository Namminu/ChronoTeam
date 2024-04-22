// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Fighter_TrdGimicClear.h"
#include "BossAIController.h"
#include "Boss_Fighter.h"
#include <Blueprint/AIBlueprintHelperLibrary.h>
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_Fighter_TrdGimicClear::UBTTask_Fighter_TrdGimicClear()
{
	NodeName = TEXT("Fighter Trd Gimic Clear");
}

EBTNodeResult::Type UBTTask_Fighter_TrdGimicClear::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto const* const cont = OwnerComp.GetAIOwner();
	auto* const Fighter = Cast<ABoss_Fighter>(cont->GetPawn());

	Fighter->SetMontageEnd(false);

	UAIBlueprintHelperLibrary::GetAIController(Fighter)->GetBlackboardComponent()->SetValueAsBool("IsTrdGimic", false);
	UAIBlueprintHelperLibrary::GetAIController(Fighter)->GetBlackboardComponent()->SetValueAsBool("IsGimic", false);
	UAIBlueprintHelperLibrary::GetAIController(Fighter)->GetBlackboardComponent()->SetValueAsBool("IsMontageEnd", false);

	return EBTNodeResult::Succeeded;
}
