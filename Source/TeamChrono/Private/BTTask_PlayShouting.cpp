// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_PlayShouting.h"
#include "BaseEliteMonster.h"
#include "AIController.h"

UBTTask_PlayShouting::UBTTask_PlayShouting(FObjectInitializer const& ObjectInitializer)
{
	NodeName = TEXT("Play Shouting");
}

EBTNodeResult::Type UBTTask_PlayShouting::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//Cast to Elite Monster
	auto const* const cont = OwnerComp.GetAIOwner();
	auto* const EliteMonster = Cast<ABaseEliteMonster>(cont->GetPawn());

	EliteMonster->GetMesh()->AddRadialImpulse(EliteMonster->GetActorLocation(), Radius, Strength, ERadialImpulseFalloff::RIF_Linear, false);

	return EBTNodeResult::Succeeded;
}