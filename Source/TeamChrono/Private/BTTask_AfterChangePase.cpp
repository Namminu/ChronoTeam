// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_AfterChangePase.h"
#include "BossAIController.h"
#include "Boss_TimeMaster.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

UBTTask_AfterChangePase::UBTTask_AfterChangePase()
{
	NodeName = TEXT("After Change Pase, Back To MainTree");
}

EBTNodeResult::Type UBTTask_AfterChangePase::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (auto const* const cont = OwnerComp.GetAIOwner())
	{
		if (auto* const Chrono = Cast<ABoss_TimeMaster>(cont->GetPawn()))
		{
			if (Chrono->GetBossPase() == 2)
			{
				Chrono->Boss2PaseAttachPin();

				UAIBlueprintHelperLibrary::GetAIController(Chrono)->GetBlackboardComponent()->SetValueAsBool("ChangePase", false);
			}
			else if (Chrono->GetBossPase() == 3)
			{
				Chrono->Boss3PaseAttachPin();

				UAIBlueprintHelperLibrary::GetAIController(Chrono)->GetBlackboardComponent()->SetValueAsBool("ChangePase", false);
			}

			return EBTNodeResult::Succeeded;
		}

	}
	return EBTNodeResult::Failed;
}
