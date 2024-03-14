// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_LookatPlayer.h"
#include "kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "AI_Controller_.h"
#include <Kismet/KismetMathLibrary.h>

UBTTask_LookatPlayer::UBTTask_LookatPlayer(FObjectInitializer const& ObjectInitializer)
{
	NodeName = TEXT("Look At Player");
}

EBTNodeResult::Type UBTTask_LookatPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//Get Player Location
	if (auto* const player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
	{
		//get player location to use as an origin
		auto const playerLocation = player->GetActorLocation();

		//Get AI Controller and it's npc
		if (AAI_Controller_* const cont = Cast<AAI_Controller_>(OwnerComp.GetAIOwner()))
		{
			if (auto* const ai = cont->GetPawn())
			{
				//obtain npc location to use as on origin
				auto const Origin = ai->GetActorLocation();

				FRotator changeRotation = UKismetMathLibrary::FindLookAtRotation(Origin, playerLocation);
				FRotator newRotation = FRotator(0, changeRotation.Yaw, changeRotation.Roll);
				//Set Ai rotation to Look at Player
				ai->SetActorRotation(newRotation);
				//ai->SetActorRelativeRotation(newRotation);
			}
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Look At Player TaskNode : Cast failed to ai_controller_"));
		}
		
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
