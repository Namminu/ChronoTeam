// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_ChronoLookPlayer.h"
#include "Boss_TimeMaster.h"
#include "BossAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Boss_Chrono_ShadowPartner.h"

UBTTask_ChronoLookPlayer::UBTTask_ChronoLookPlayer()
{
	NodeName = TEXT("Chrono Looks Player");
}

EBTNodeResult::Type UBTTask_ChronoLookPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (auto const* const cont = OwnerComp.GetAIOwner())
	{
		if (OwnerComp.GetOwner()->ActorHasTag("SHAPA"))
		{
			if (auto* const Shapa = Cast<ABoss_Chrono_ShadowPartner>(cont->GetPawn()))
			{
				Shapa->StayLookPlayer(OwnerComp.GetBlackboardComponent()->GetValueAsVector(GetSelectedBlackboardKey()), GetRandomFloat(minTime, maxTime));
			}
		}
		else
		{
			if (auto* const Chrono = Cast<ABoss_TimeMaster>(cont->GetPawn()))
			{
				Chrono->StayLookPlayer(OwnerComp.GetBlackboardComponent()->GetValueAsVector(GetSelectedBlackboardKey()), GetRandomFloat(minTime, maxTime));
			}
		}	
	}
	
	return EBTNodeResult::Succeeded;
}

float UBTTask_ChronoLookPlayer::GetRandomFloat(float min, float max)
{
	return FMath::RandRange(min, max);
}
