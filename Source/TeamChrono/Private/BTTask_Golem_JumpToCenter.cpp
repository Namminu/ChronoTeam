// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Golem_JumpToCenter.h"
#include "BossAIController.h"
#include "Boss_Golem.h"

UBTTask_Golem_JumpToCenter::UBTTask_Golem_JumpToCenter()
{
	NodeName = TEXT("Golem Jump To Center");
}

EBTNodeResult::Type UBTTask_Golem_JumpToCenter::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (auto const* cont = Cast<ABossAIController>(OwnerComp.GetAIOwner()))
	{
		if (ABoss_Golem* const Boss = Cast<ABoss_Golem>(cont->GetPawn()))
		{
			if (!bIsJumpStart)
			{
				Boss->SndGimicJumpToCenter();
				//Boss->SndGimicJumpToCenter_Implementation();
				bIsJumpStart = true;
			}
			
			if (Boss->GetSndJumping())
			{
				return EBTNodeResult::Failed;
			}
			else return EBTNodeResult::Succeeded;

		}
		else return EBTNodeResult::Failed;

	}
	else return EBTNodeResult::Failed;
}