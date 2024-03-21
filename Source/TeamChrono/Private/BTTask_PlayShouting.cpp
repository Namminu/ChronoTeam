// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_PlayShouting.h"
#include "BaseEliteMonster.h"
#include "AIController.h"
#include <TeamChrono/TeamChronoCharacter.h>
#include "Components/CapsuleComponent.h"
#include <Kismet/GameplayStatics.h>

UBTTask_PlayShouting::UBTTask_PlayShouting(FObjectInitializer const& ObjectInitializer)
{
	NodeName = TEXT("Play Shouting");
}

EBTNodeResult::Type UBTTask_PlayShouting::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//Cast to Elite Monster
	auto const* const cont = OwnerComp.GetAIOwner();
	auto* const EliteMonster = Cast<ABaseEliteMonster>(cont->GetPawn());

	ATeamChronoCharacter* player = Cast<ATeamChronoCharacter>(UGameplayStatics::GetPlayerCharacter(this,0));
	if(player)
	{
		player->GetCapsuleComponent()->SetSimulatePhysics(true);
		UE_LOG(LogTemp, Error, TEXT("Player Simulate : %s"), player->GetCapsuleComponent()->IsSimulatingPhysics() ? TEXT("true") : TEXT("false"));
		EliteMonster->GetMesh()->AddRadialImpulse(EliteMonster->GetActorLocation(), Radius, Strength, ERadialImpulseFalloff::RIF_Linear, false);
		player->GetCapsuleComponent()->SetSimulatePhysics(false);
		UE_LOG(LogTemp, Error, TEXT("Player Simulate : %s"), player->GetCapsuleComponent()->IsSimulatingPhysics() ? TEXT("true") : TEXT("false"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Cast Failed"));
	}
	


	return EBTNodeResult::Succeeded;
}
