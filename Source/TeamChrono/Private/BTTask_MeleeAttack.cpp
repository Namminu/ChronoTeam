
// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_MeleeAttack.h"
#include "CombatInterface.h"
#include "AIController.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Engine/LatentActionManager.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimMontage.h"
#include "Animation/AnimInstance.h"

UBTTask_MeleeAttack::UBTTask_MeleeAttack()
{
	NodeName = TEXT("Melee Attack");
}

EBTNodeResult::Type UBTTask_MeleeAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//if monster out of Range, do not attack the player
	auto const OutOfRange = !OwnerComp.GetBlackboardComponent()->GetValueAsBool(GetSelectedBlackboardKey());
	if (OutOfRange)	//플레이어가 몬스터의 공격 범위를 벗어났을 때
	{
		//finish the task
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return EBTNodeResult::Succeeded;
	}

	//monster in range so get the AI's controller and the Monster itself
	auto const* const cont = OwnerComp.GetAIOwner();
	auto* const Monster = Cast<ABaseMonster>(cont->GetPawn());

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

bool UBTTask_MeleeAttack::MontageHasFinished(ABaseMonster* const Monster)
{
	return Monster->GetMesh()->GetAnimInstance()->Montage_GetIsStopped(Monster->GetAtkMontage());
}
