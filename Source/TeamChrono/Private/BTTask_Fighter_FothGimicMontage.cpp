// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Fighter_FothGimicMontage.h"
#include "BossAIController.h"
#include "Boss_Fighter.h"

UBTTask_Fighter_FothGimicMontage::UBTTask_Fighter_FothGimicMontage()
{
	NodeName = TEXT("Fighter Foth Gimic Aura Montage");
}

EBTNodeResult::Type UBTTask_Fighter_FothGimicMontage::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (auto const* const cont = OwnerComp.GetAIOwner())
	{
		if (auto* const Fighter = Cast<ABoss_Fighter>(cont->GetPawn()))
		{
			if (!Fighter->GetFothMontageING())
			{
				Fighter->SetInvincible(true);
				Fighter->FothGimicMontage();

				return EBTNodeResult::Failed;
			}
			else
			{
				if (Fighter->GetFothMontageEnd())
				{
					return EBTNodeResult::Succeeded;
				}
				else return EBTNodeResult::Failed;

			}
		}
		else return EBTNodeResult::Failed;

	}
	else return EBTNodeResult::Failed;
}
