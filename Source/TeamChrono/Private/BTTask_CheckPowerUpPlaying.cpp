// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_CheckPowerUpPlaying.h"
#include "BaseEliteMonster.h"
#include "AI_Controller_.h"

UBTTask_CheckPowerUpPlaying::UBTTask_CheckPowerUpPlaying(FObjectInitializer const& ObjectInitializer)
{
	NodeName = TEXT("Check Is PowerUp Anim Playing");
}

EBTNodeResult::Type UBTTask_CheckPowerUpPlaying::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto const* const cont = OwnerComp.GetAIOwner();
	auto* const EliteMonster = Cast<ABaseEliteMonster>(cont->GetPawn());

	EliteMonster->SetPowerUpPlaying(isPlaying);

	return EBTNodeResult::Succeeded;
}
