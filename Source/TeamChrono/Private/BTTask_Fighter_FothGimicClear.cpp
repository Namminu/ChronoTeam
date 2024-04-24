// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Fighter_FothGimicClear.h"
#include "BossAIController.h"
#include "Boss_Fighter.h"
#include <Blueprint/AIBlueprintHelperLibrary.h>
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_Fighter_FothGimicClear::UBTTask_Fighter_FothGimicClear()
{
	NodeName = TEXT("Fighter Foth Gimic Clear");
}

EBTNodeResult::Type UBTTask_Fighter_FothGimicClear::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto const* const cont = OwnerComp.GetAIOwner();
	auto* const Fighter = Cast<ABoss_Fighter>(cont->GetPawn());

	Fighter->SetMontageEnd(false);
	Fighter->SetFothMontageING(false);
	Fighter->SetFothMontageEnd(false);
	//Clear Properties
	UAIBlueprintHelperLibrary::GetAIController(Fighter)->GetBlackboardComponent()->SetValueAsBool("IsFothGimic", false);
	UAIBlueprintHelperLibrary::GetAIController(Fighter)->GetBlackboardComponent()->SetValueAsBool("IsGimic", false);
	UAIBlueprintHelperLibrary::GetAIController(Fighter)->GetBlackboardComponent()->SetValueAsBool("IsMontageEnd", false);

	Fighter->SetInvincible(false);
	Fighter->SetIsFothGimicING(false);

	return EBTNodeResult::Succeeded;
}
