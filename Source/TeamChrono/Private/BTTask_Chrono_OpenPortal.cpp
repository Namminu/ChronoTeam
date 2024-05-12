// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Chrono_OpenPortal.h"
#include "Boss_TimeMaster.h"
#include "BossAIController.h"

UBTTask_Chrono_OpenPortal::UBTTask_Chrono_OpenPortal()
{
	NodeName = TEXT("Chrono Open Portal");
}

EBTNodeResult::Type UBTTask_Chrono_OpenPortal::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (auto const* const cont = OwnerComp.GetAIOwner())
	{
		if (auto* const Chrono = Cast<ABoss_TimeMaster>(cont->GetPawn()))
		{
			Chrono->OpenOtherBossPortal(Chrono->GetBossPase());

			return EBTNodeResult::Succeeded;
		}

	}
	return EBTNodeResult::Failed;
}
