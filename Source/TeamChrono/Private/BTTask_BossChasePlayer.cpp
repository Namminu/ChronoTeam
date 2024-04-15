// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_BossChasePlayer.h"
#include "BossAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Base_Boss.h"

UBTTask_BossChasePlayer::UBTTask_BossChasePlayer(FObjectInitializer const& ObjectInitializer)
{
	NodeName = TEXT("Boss Chase Player");
}

EBTNodeResult::Type UBTTask_BossChasePlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//get target location from blackboard via the ai's controller
	if (auto* const cont = Cast<ABossAIController>(OwnerComp.GetAIOwner()))
	{
		auto const PlayerLocation = OwnerComp.GetBlackboardComponent()->GetValueAsVector(GetSelectedBlackboardKey());

		//move to player's location
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(cont, PlayerLocation);
		//finish with success
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
