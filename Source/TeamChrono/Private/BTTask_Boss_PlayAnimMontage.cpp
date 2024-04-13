// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Boss_PlayAnimMontage.h"
#include "Base_Boss.h"
#include "BossAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_Boss_PlayAnimMontage::UBTTask_Boss_PlayAnimMontage(FObjectInitializer const& ObjectInitializer)
{
	NodeName = TEXT("Boss Play Montage");
}

EBTNodeResult::Type UBTTask_Boss_PlayAnimMontage::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (Montage)
	{
		auto const* const cont = OwnerComp.GetAIOwner();
		ABase_Boss* const Boss = Cast<ABase_Boss>(cont->GetPawn());

		if (!Boss->GetMontageEnd())
		{
			Boss->PlayMontage(Montage);
			Boss->SetMontageEnd(true);
		}

		if (checkPlaying(Boss))
		{
			return EBTNodeResult::Succeeded;
		}
		else return EBTNodeResult::Failed;

	}
	return EBTNodeResult::Failed;
}

bool UBTTask_Boss_PlayAnimMontage::checkPlaying(class ABase_Boss* const Boss)
{
	//While Montage is Playing : return False
	//While Montage is End : return true
	return !(Boss->GetMesh()->GetAnimInstance()->IsAnyMontagePlaying());
}