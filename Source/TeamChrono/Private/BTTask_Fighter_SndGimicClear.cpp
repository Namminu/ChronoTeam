// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Fighter_SndGimicClear.h"
#include "BossAIController.h"
#include "Boss_Fighter.h"
#include <Blueprint/AIBlueprintHelperLibrary.h>
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_Fighter_SndGimicClear::UBTTask_Fighter_SndGimicClear()
{
	NodeName = TEXT("Fighter Snd Gimic Clear");
}

EBTNodeResult::Type UBTTask_Fighter_SndGimicClear::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto const* const cont = OwnerComp.GetAIOwner();
	auto* const Fighter = Cast<ABoss_Fighter>(cont->GetPawn());

	Fighter->ClearTornadoArray();
	Fighter->SetMontageEnd(false);

	UAIBlueprintHelperLibrary::GetAIController(Fighter)->GetBlackboardComponent()->SetValueAsBool("IsSndGimic", false);
	UAIBlueprintHelperLibrary::GetAIController(Fighter)->GetBlackboardComponent()->SetValueAsBool("IsGimic", false);
	UAIBlueprintHelperLibrary::GetAIController(Fighter)->GetBlackboardComponent()->SetValueAsBool("IsMontageEnd", false);

	Fighter->SetSndGimicTimer();

	return EBTNodeResult::Succeeded;
}
