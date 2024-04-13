// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Golem_SndGimicClear.h"
#include "Boss_Golem.h"
#include "BossAIController.h"
#include <Blueprint/AIBlueprintHelperLibrary.h>
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_Golem_SndGimicClear::UBTTask_Golem_SndGimicClear()
{
	NodeName = TEXT("Snd Gimic End");
}

EBTNodeResult::Type UBTTask_Golem_SndGimicClear::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto const* const cont = OwnerComp.GetAIOwner();
	auto* const Boss = Cast<ABase_Boss>(cont->GetPawn());
	auto* const Golem = Cast<ABoss_Golem>(cont->GetPawn());

	//Clear Properties
	Boss->SetMontageEnd(false);
	Golem->SetSndGimicIng(false);
	Golem->SetSndJumpCenterEnd(false);

	UAIBlueprintHelperLibrary::GetAIController(Golem)->GetBlackboardComponent()->SetValueAsBool("IsGimic", false);
	UAIBlueprintHelperLibrary::GetAIController(Golem)->GetBlackboardComponent()->SetValueAsBool("IsMontageEnd", false);
	UAIBlueprintHelperLibrary::GetAIController(Golem)->GetBlackboardComponent()->SetValueAsBool("IsTimeGimic", false);

	UE_LOG(LogTemp, Warning, TEXT("Snd Gimic Clear"));

	//Resume Gimic Timer
	Golem->SetStartSndTimer();

	return EBTNodeResult::Succeeded;
}
