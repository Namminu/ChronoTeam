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
			if (!bFunctionsCalled)
			{
				//Set Focus To Player When Gimic Ing
				Golem->SetFocusToPlayer();
				//Call Fst Gimic Func
				Golem->StartFstGimicTimer();

				// Mark that functions have been called
				bFunctionsCalled = true;
			}

			//Check Fst Gimic is Playing
			if (Golem->GetFstGimicIng())
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
