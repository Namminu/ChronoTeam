// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_StayFromPlayer.h"
#include "Boss_TimeMaster.h"
#include "BossAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_StayFromPlayer::UBTTask_StayFromPlayer()
{
	NodeName = TEXT("Keep Away From Player");
}

EBTNodeResult::Type UBTTask_StayFromPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (auto const* const cont = OwnerComp.GetAIOwner())
	{
		if (auto* const Chrono = Cast<ABoss_TimeMaster>(cont->GetPawn()))
		{
			Chrono->SetFarfromPlayer(Chrono->GetPlayerByDistance(), GetRandomFloat(minTime, maxTime));
		}
	}
	return EBTNodeResult::Succeeded;
}

float UBTTask_StayFromPlayer::GetRandomFloat(float min, float max)
{
	return FMath::RandRange(min, max);
}
