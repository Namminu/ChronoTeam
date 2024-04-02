// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_ResetTargetLocation.h"
#include "BaseMonster.h"
#include "AI_Controller_.h"
#include <Blueprint/AIBlueprintHelperLibrary.h>
#include "BehaviorTree/BlackboardComponent.h"
#include <Kismet/GameplayStatics.h>

UBTService_ResetTargetLocation::UBTService_ResetTargetLocation()
{
	bNotifyBecomeRelevant = true;
	NodeName = TEXT("Reset Target Location");
}

void UBTService_ResetTargetLocation::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnBecomeRelevant(OwnerComp, NodeMemory);
	if (auto const Cont = OwnerComp.GetAIOwner())
	{
		if (auto* const Monster = Cast<ABaseMonster>(Cont->GetPawn()))
		{
			isAttack = UAIBlueprintHelperLibrary::GetAIController(Monster)->GetBlackboardComponent()->GetValueAsBool("PlayerIsInAttackRange");
			//isBarrier = UAIBlueprintHelperLibrary::GetAIController(Monster)->GetBlackboardComponent()->GetValueAsBool("CanTakeDamage");

			//While Monster Start Attack or Gimic Start
			if (isAttack)
			{
				//Set TargetLocation BB key to Actor(self) Location, So Don't Move when Finish Attack
				OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetActorLocation());

				UE_LOG(LogTemp, Warning, TEXT("TargetLocation Reset"));
			}
		}
	}
}
