// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Golem_FothGimic_GoMainBT.h"
#include "BossAIController.h"
#include "Boss_Golem.h"
#include <Blueprint/AIBlueprintHelperLibrary.h>
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_Golem_FothGimic_GoMainBT::UBTTask_Golem_FothGimic_GoMainBT()
{
	NodeName = TEXT("Go To Main BT");
}

EBTNodeResult::Type UBTTask_Golem_FothGimic_GoMainBT::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (auto const* const cont = OwnerComp.GetAIOwner())
	{
		auto* const Boss = Cast<ABase_Boss>(cont->GetPawn());
		if (auto* const Golem = Cast<ABoss_Golem>(cont->GetPawn()))
		{
			Golem->SetResumeSndTimer();
			Golem->SetFothGimicIng(true);
			Golem->SetInvincible(false);
			Boss->SetMontageEnd(false);

			UAIBlueprintHelperLibrary::GetAIController(Golem)->GetBlackboardComponent()->SetValueAsBool("FouthGimic", false);

			return EBTNodeResult::Succeeded;
		}
		else return EBTNodeResult::Failed;

	}
	else return EBTNodeResult::Failed;
	
}