// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Fighter_FstGimicClear.h"
#include "BossAIController.h"
#include "Boss_Fighter.h"
#include <Blueprint/AIBlueprintHelperLibrary.h>
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_Fighter_FstGimicClear::UBTTask_Fighter_FstGimicClear()
{
	NodeName = TEXT("Fighter_FstGimic Clear");
}

EBTNodeResult::Type UBTTask_Fighter_FstGimicClear::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto const* const cont = OwnerComp.GetAIOwner();
	auto* const Fighter = Cast<ABoss_Fighter>(cont->GetPawn());

	Fighter->ClearMarbleArray();
	UE_LOG(LogTemp, Error, TEXT("%d"), Fighter->GetMarbleArray().Num());
	Fighter->SetMontageEnd(false);
	UAIBlueprintHelperLibrary::GetAIController(Fighter)->GetBlackboardComponent()->SetValueAsBool("IsFstGimic", false);
	UAIBlueprintHelperLibrary::GetAIController(Fighter)->GetBlackboardComponent()->SetValueAsBool("IsGimic", false);
	UAIBlueprintHelperLibrary::GetAIController(Fighter)->GetBlackboardComponent()->SetValueAsBool("IsMontageEnd", false);

	return EBTNodeResult::Succeeded;
}
