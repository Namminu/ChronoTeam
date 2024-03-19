// Fill out your copyright notice in the Description page of Project Settings.

#include "yBTTask_SetFocusOnPlayer.h"
#include <Kismet/GameplayStatics.h>
#include "AI_Controller_.h"
#include "GameFramework/Character.h"

UyBTTask_SetFocusOnPlayer::UyBTTask_SetFocusOnPlayer(FObjectInitializer const& ObjectInitializer)
{
	NodeName = TEXT("Set Focus On Player");
}

EBTNodeResult::Type UyBTTask_SetFocusOnPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//Get Player Location
	if (auto* const player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
	{
		//get player location to use as an origin
		auto const playerLocation = player->GetActorLocation();

		//Get AI Controller and it's npc
		if (AAI_Controller_* const cont = Cast<AAI_Controller_>(OwnerComp.GetAIOwner()))
		{
			cont->SetFocus(player);
		}
	}
	return EBTNodeResult::Succeeded;
}
