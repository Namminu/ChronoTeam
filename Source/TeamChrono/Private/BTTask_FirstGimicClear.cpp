// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FirstGimicClear.h"
#include "Boss_Golem.h"
#include "BossAIController.h"
#include <Blueprint/AIBlueprintHelperLibrary.h>
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_FirstGimicClear::UBTTask_FirstGimicClear()
{
	NodeName = TEXT("First Gimic End");
}

EBTNodeResult::Type UBTTask_FirstGimicClear::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto const* const cont = OwnerComp.GetAIOwner();
	auto* const Golem = Cast<ABoss_Golem>(cont->GetPawn());

	//Clear Properties
	UAIBlueprintHelperLibrary::GetAIController(Golem)->GetBlackboardComponent()->SetValueAsBool("FirstGimic", false);
	UAIBlueprintHelperLibrary::GetAIController(Golem)->GetBlackboardComponent()->SetValueAsBool("IsGimic", false);
	UAIBlueprintHelperLibrary::GetAIController(Golem)->GetBlackboardComponent()->SetValueAsBool("IsMontageEnd", false);

	Golem->SetResumeSndTimer();

	return EBTNodeResult::Succeeded;
}
