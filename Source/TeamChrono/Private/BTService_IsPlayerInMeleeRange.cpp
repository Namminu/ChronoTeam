// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_IsPlayerInMeleeRange.h"
#include "BaseMonster.h"
#include "AI_Controller_.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Runtime//Engine/Classes/Engine/World.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_IsPlayerInMeleeRange::UBTService_IsPlayerInMeleeRange()
{
	bNotifyBecomeRelevant = true;
	NodeName = TEXT("Is Player In MeleeRange");
}

void UBTService_IsPlayerInMeleeRange::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//Get Controller and Monster
	auto const* const cont = Cast<AAI_Controller_>(OwnerComp.GetAIOwner());
	auto const* const Monster = Cast<ABaseMonster>(cont->GetPawn());

	//Get Player Character
	auto const* const player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	//Write true or false to the blackboard key depending on whether or no the player is in range
	//Monster ���� Player ������ �Ÿ� ���� : MeleeRange ���� ª���� true, �ָ� false
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(), Monster->GetDistanceTo(player) <= MeleeRange);
	//OwnerComp.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(), Monster->GetDistanceTo(player) <= MeleeRange * Monster->GetMonAtkRange());
}
