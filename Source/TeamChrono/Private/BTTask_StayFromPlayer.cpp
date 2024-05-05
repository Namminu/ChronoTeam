// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_StayFromPlayer.h"
#include "Boss_TimeMaster.h"
#include "BossAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

UBTTask_StayFromPlayer::UBTTask_StayFromPlayer()
{
	NodeName = TEXT("Keep Away From Player");
}

EBTNodeResult::Type UBTTask_StayFromPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (auto* const cont = Cast<ABossAIController>(OwnerComp.GetAIOwner()))
	{
		if (auto* const Chrono = Cast<ABoss_TimeMaster>(cont->GetPawn()))
		{
			//Chrono->SetFarfromPlayer(Chrono->GetCenterByDistance(), GetRandomFloat(minTime, maxTime));

			currentAngle += RotateSpeed * GetWorld()->DeltaTimeSeconds;

			FVector CircleLocation = Chrono->GetCenterArrow()->GetActorLocation() 
				+ FVector(OrbitDistance * FMath::Cos(currentAngle), OrbitDistance * FMath::Sin(currentAngle), 0);

			FVector newLocation = FVector(CircleLocation.X, CircleLocation.Y, Chrono->GetCenterArrow()->GetActorLocation().Z + 400);

			Chrono->SetActorLocation(newLocation);

			return EBTNodeResult::Succeeded;
		}
	}

	return EBTNodeResult::Failed;
}

float UBTTask_StayFromPlayer::GetRandomFloat(float min, float max)
{
	return FMath::RandRange(min, max);
}
