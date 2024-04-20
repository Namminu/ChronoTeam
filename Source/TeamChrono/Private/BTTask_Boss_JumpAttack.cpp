// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Boss_JumpAttack.h"
#include "BossAIController.h"
#include "Base_Boss.h"

UBTTask_Boss_JumpAttack::UBTTask_Boss_JumpAttack()
{
	NodeName = TEXT("Boss Jump Attack");
}

EBTNodeResult::Type UBTTask_Boss_JumpAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (auto const* cont = Cast<ABossAIController>(OwnerComp.GetAIOwner()))
	{
		if (ABase_Boss* const Boss = Cast<ABase_Boss>(cont->GetPawn()))
		{
			Boss->AttackFunc(2);
			return EBTNodeResult::Succeeded;
		}
		else return EBTNodeResult::Failed;

	}
	else return EBTNodeResult::Failed;
}
