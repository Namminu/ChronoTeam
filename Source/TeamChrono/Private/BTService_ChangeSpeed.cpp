// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_ChangeSpeed.h"
#include "BaseMonster.h"
#include "AIController.h"
#include "GameFramework/CharacterMovementComponent.h"

UBTService_ChangeSpeed::UBTService_ChangeSpeed()
{
	bNotifyBecomeRelevant = true;
	NodeName = TEXT("Chane Speed");
}

void UBTService_ChangeSpeed::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnBecomeRelevant(OwnerComp, NodeMemory);
	if (auto const Cont = OwnerComp.GetAIOwner())
	{
		if (auto* const Monster = Cast<ABaseMonster>(Cont->GetPawn()))
		{
			Monster->GetCharacterMovement()->MaxWalkSpeed = chaseSpeed;
		}
	}
}
