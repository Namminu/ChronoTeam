// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Golem_SoFarAndJumpAttack.h"
#include "Boss_Golem.h"
#include "BossAIController.h"

UBTTask_Golem_SoFarAndJumpAttack::UBTTask_Golem_SoFarAndJumpAttack()
{
	NodeName = TEXT("Jump Attack");
}

EBTNodeResult::Type UBTTask_Golem_SoFarAndJumpAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (auto const* cont = Cast<ABossAIController>(OwnerComp.GetAIOwner()))
	{
		if (ABoss_Golem* const Boss = Cast<ABoss_Golem>(cont->GetPawn()))
		{
			Boss->AttackFunc(2);
			return EBTNodeResult::Succeeded;
		}
		else return EBTNodeResult::Failed;
	}
	else return EBTNodeResult::Failed;

}