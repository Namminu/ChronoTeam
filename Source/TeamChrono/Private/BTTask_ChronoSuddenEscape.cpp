// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_ChronoSuddenEscape.h"
#include "Boss_TimeMaster.h"
#include "BossAIController.h"

UBTTask_ChronoSuddenEscape::UBTTask_ChronoSuddenEscape()
{
	NodeName = TEXT("Sudden Escape");
}

EBTNodeResult::Type UBTTask_ChronoSuddenEscape::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (auto* const cont = Cast<ABossAIController>(OwnerComp.GetAIOwner()))
	{
		if (auto* const Chrono = Cast<ABoss_TimeMaster>(cont->GetPawn()))
		{
			if (!Chrono->GetEscapse())
			{
				Chrono->SuddenEscapeFromPlayer();
				Chrono->SetEscape(true);
			}
		}
	}
	return EBTNodeResult::Succeeded;
}
