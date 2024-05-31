// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_GolemFstGimicSetFuncTime.h"
#include "BossAIController.h"
#include "Base_Boss.h"
#include "Boss_Golem.h"

UBTTask_GolemFstGimicSetFuncTime::UBTTask_GolemFstGimicSetFuncTime()
{
	NodeName = TEXT("First Gimic Task");
}

EBTNodeResult::Type UBTTask_GolemFstGimicSetFuncTime::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (auto const* cont = Cast<ABossAIController>(OwnerComp.GetAIOwner()))
	{
		if (ABoss_Golem* const Golem = Cast<ABoss_Golem>(cont->GetPawn()))
		{
			if (!Golem->GetFstGimicStart())
			{
				//Call Fst Gimic Func
				Golem->StartFstGimicTimer();
				Golem->SetFstGimicStart(true);
			}

			//Check Fst Gimic is Playing
			if (Golem->GetFstGimicStart())
			{					
				//Still Fst Gimic Playing
				return EBTNodeResult::Failed;
			}
			//Fst Gimic Clear
			else return EBTNodeResult::Succeeded;

		}
		else return EBTNodeResult::Failed;

	}
	else return EBTNodeResult::Failed;

	return EBTNodeResult::Type();
}
