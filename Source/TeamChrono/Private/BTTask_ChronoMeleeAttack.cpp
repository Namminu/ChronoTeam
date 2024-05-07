// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_ChronoMeleeAttack.h"
#include "Boss_TimeMaster.h"
#include "BossAIController.h"


UBTTask_ChronoMeleeAttack::UBTTask_ChronoMeleeAttack()
{
	NodeName = TEXT("Chrono Melee Attack");
}

EBTNodeResult::Type UBTTask_ChronoMeleeAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//monster in range so get the AI's controller and the Monster itself
	auto const* const cont = OwnerComp.GetAIOwner();
	auto* const Monster = Cast<ABoss_TimeMaster>(cont->GetPawn());

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

bool UBTTask_ChronoMeleeAttack::MontageHasFinished(ABoss_TimeMaster* const Monster)
{
	return !(Monster->GetMesh()->GetAnimInstance()->IsAnyMontagePlaying());
}
