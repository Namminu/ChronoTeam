// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_SndGimicJumpToCenter.h"
#include "BossAIController.h"
#include "Boss_Golem.h"

UBTTask_SndGimicJumpToCenter::UBTTask_SndGimicJumpToCenter()
{
	NodeName = TEXT("Jump to Center");
}

EBTNodeResult::Type UBTTask_SndGimicJumpToCenter::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (auto const* cont = Cast<ABossAIController>(OwnerComp.GetAIOwner()))
	{
		if (ABoss_Golem* const Golem = Cast<ABoss_Golem>(cont->GetPawn()))
		{
			if (!isTaskCalled)
			{
				Golem->SndGimicJumpToCenter_Implementation();
				isTaskCalled = true;
			}

			if (Golem->GetSndJumping())
			{
				return EBTNodeResult::Failed;
			}
			else return EBTNodeResult::Succeeded;

		}
		else return EBTNodeResult::Failed;

	}
	else return EBTNodeResult::Failed;
}