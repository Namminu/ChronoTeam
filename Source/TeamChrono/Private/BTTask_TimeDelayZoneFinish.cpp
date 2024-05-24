// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_TimeDelayZoneFinish.h"
#include "BossAIController.h"
#include "Boss_TimeMaster.h"
#include <Blueprint/AIBlueprintHelperLibrary.h>
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_TimeDelayZoneFinish::UBTTask_TimeDelayZoneFinish()
{
	NodeName = TEXT("TimeDelayZone Finish");
}

EBTNodeResult::Type UBTTask_TimeDelayZoneFinish::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (auto const* const cont = OwnerComp.GetAIOwner())
	{
		if (auto* const Chrono = Cast<ABoss_TimeMaster>(cont->GetPawn()))
		{
			Chrono->SetMontageEnd(false);

			UAIBlueprintHelperLibrary::GetAIController(Chrono)->GetBlackboardComponent()->SetValueAsBool("IsMontageEnd", false);
			UAIBlueprintHelperLibrary::GetAIController(Chrono)->GetBlackboardComponent()->SetValueAsBool("ChangeSetup", false);
			UAIBlueprintHelperLibrary::GetAIController(Chrono)->GetBlackboardComponent()->SetValueAsBool("IsAttack", false);

			Chrono->SetAttackTimer();
		}
	}

	return EBTNodeResult::Type();
}
