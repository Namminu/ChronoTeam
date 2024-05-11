// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Shapa_MeleeAttack.h"
#include "Boss_Chrono_ShadowPartner.h"
#include "BossAIController.h"

UBTTask_Shapa_MeleeAttack::UBTTask_Shapa_MeleeAttack()
{
	NodeName = TEXT("Shapa Melee Attack");
}

EBTNodeResult::Type UBTTask_Shapa_MeleeAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto const* const cont = OwnerComp.GetAIOwner();
	auto* const Monster = Cast<ABoss_Chrono_ShadowPartner>(cont->GetPawn());

	//if the Monster supports the ICombatInterface, cast and call the Execute_MeleeAttack function 
	if (auto* const icombat = Cast<ICombatInterface>(Monster))
	{
		//necessary check to see if the montage has finished so we dont try and play it again
		if (MontageHasFinished(Monster))
		{
			icombat->Execute_MeleeAttack(Monster);
		}
	}

	//finish the task
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Type();
}

bool UBTTask_Shapa_MeleeAttack::MontageHasFinished(ABoss_Chrono_ShadowPartner* const Monster)
{
	return !(Monster->GetMesh()->GetAnimInstance()->IsAnyMontagePlaying());
}
