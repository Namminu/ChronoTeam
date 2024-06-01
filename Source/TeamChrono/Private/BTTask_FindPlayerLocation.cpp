// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindPlayerLocation.h"
#include "kismet/GameplayStatics.h"
#include "NavigationSystem.h"
#include "GameFramework/Character.h"
#include "BehaviorTree/BlackboardComponent.h"
#include <TeamChrono/TeamChronoCharacter.h>

UBTTask_FindPlayerLocation::UBTTask_FindPlayerLocation(FObjectInitializer const& ObjectInitializer)
{
	NodeName = TEXT("Find Player Location");
}

EBTNodeResult::Type UBTTask_FindPlayerLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	////get player character
	//if (auto* const player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
	//{
	//	//get player location to use as an origin
	//	auto const playerLocation = player->GetActorLocation();
	//	if (SearchRandom)	//랜덤 순회 시
	//	{
	//		FNavLocation loc;

	//		//get the navigation system and generate a random location near the player
	//		if (auto* const NavSys = UNavigationSystemV1::GetCurrent(GetWorld()))
	//		{
	//			//try to get a random location near the player
	//			if (NavSys->GetRandomPointInNavigableRadius(playerLocation, SearchRadius, loc))
	//			{
	//				OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), loc.Location);
	//				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	//				return EBTNodeResult::Succeeded;
	//			}
	//		}
	//	}
	//	else //플레이어 추격 시
	//	{
	//		OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), playerLocation);
	//		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	//		return EBTNodeResult::Succeeded;
	//	}
	//}

	//Get Player Character
	if (ATeamChronoCharacter* const player = Cast<ATeamChronoCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)))
	{
		FVector const targetLocation = player->GetActorLocation();

		OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), targetLocation);
		//FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);

		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
