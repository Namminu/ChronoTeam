// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_PlayAnimMontage.h"
#include "AIController.h"
#include "BaseMonster.h"

UBTTask_PlayAnimMontage::UBTTask_PlayAnimMontage(FObjectInitializer const& ObjectInitializer)
{
	NodeName = TEXT("Play AnimMontage");
}

EBTNodeResult::Type UBTTask_PlayAnimMontage::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (AnimMontage)
	{
		auto const* const cont = OwnerComp.GetAIOwner();
		ABaseMonster* const Monster = Cast<ABaseMonster>(cont->GetPawn());

		if (checkPlaying(Monster))
		{
			Monster->PlayMontage(AnimMontage);
		}
	}

	return EBTNodeResult::Succeeded;
}

bool UBTTask_PlayAnimMontage::checkPlaying(ABaseMonster* const Monster)
{
	//While Montage is Playing : return False
	//While Montage is End : return true
	return !(Monster->GetMesh()->GetAnimInstance()->IsAnyMontagePlaying());
}
