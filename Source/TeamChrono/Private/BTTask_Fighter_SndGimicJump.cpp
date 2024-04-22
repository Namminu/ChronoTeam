// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Fighter_SndGimicJump.h"
#include "BossAIController.h"
#include "Boss_Fighter.h"

UBTTask_Fighter_SndGimicJump::UBTTask_Fighter_SndGimicJump()
{
	NodeName = TEXT("Play Snd Gimic Jump Montage");
}

EBTNodeResult::Type UBTTask_Fighter_SndGimicJump::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (auto const* const cont = OwnerComp.GetAIOwner())
	{
		if (auto* const Fighter = Cast<ABoss_Fighter>(cont->GetPawn()))
		{
			// 
			if (Fighter->GetTornadoArray().Num() < Fighter->GetAuraMaxCount())
			{
				//Play Montage When Montage Not Playing
				if (!Fighter->GetSndJumpMonING())
				{
					Fighter->SndGimicJumpAttack();

					return EBTNodeResult::Failed;
				}
				else return EBTNodeResult::Failed;
			}
			// When Jump Current Count Same or Over Max Count
			else if (Fighter->GetTornadoArray().Num() >= Fighter->GetAuraMaxCount())
			{
				if (!Fighter->GetSndJumpMonING())
				{
					return EBTNodeResult::Succeeded;
				}
				else return EBTNodeResult::Failed;
			}
		}
		else return EBTNodeResult::Failed;

	}
	else return EBTNodeResult::Failed;

	return EBTNodeResult::Failed;
}