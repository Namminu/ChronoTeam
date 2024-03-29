// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_LookatPlayer.h"
#include "kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "AI_Controller_.h"
#include <Kismet/KismetMathLibrary.h>
#include "BaseMonster.h"

UBTTask_LookatPlayer::UBTTask_LookatPlayer(FObjectInitializer const& ObjectInitializer)
{
	NodeName = TEXT("Look At Player");
}

EBTNodeResult::Type UBTTask_LookatPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (auto* const player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
	{
		if (AAI_Controller_* const cont = Cast<AAI_Controller_>(OwnerComp.GetAIOwner()))
		{
			if (auto* const Monster = Cast<ABaseMonster>(cont->GetPawn()))
			{
				if (Monster->GetMonsterLive())
				{
					cont->SetFocus(player);
				}
			}
		}
	}
	return EBTNodeResult::Succeeded;

	////Get Player Location
	//if (auto* const player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
	//{
	//	//get player location to use as an origin
	//	auto const playerLocation = player->GetActorLocation();
	//	//Get AI Controller and it's npc
	//	if (AAI_Controller_* const cont = Cast<AAI_Controller_>(OwnerComp.GetAIOwner()))
	//	{
	//		cont->SetFocus(player);
	//		if (auto* const ai = cont->GetPawn())
	//		{
	//			//obtain npc location to use as on origin
	//			auto const Origin = ai->GetActorLocation();
	//			FRotator currentRotation = FRotator(0, ai->GetActorRotation().Yaw, 0);
	//			FRotator changeRotation = UKismetMathLibrary::FindLookAtRotation(Origin, playerLocation);
	//			FRotator newRotation = FRotator(0, changeRotation.Yaw, 0);
	//			//Set Ai rotation to Look at Player
	//			//ai->SetActorRotation(newRotation);
	//			//ai->SetActorRotation(GetRotation(currentRotation, newRotation));
	//			ai->SetActorRotation(GetRotation(currentRotation, newRotation, UGameplayStatics::GetWorldDeltaSeconds(GetWorld())));
	//		}
	//	}
	//	else
	//	{
	//		UE_LOG(LogTemp, Error, TEXT("Look At Player TaskNode : Cast failed to ai_controller_"));
	//	}
	//	
	//	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	//	return EBTNodeResult::Succeeded;
	//}
	//return EBTNodeResult::Failed;
}
