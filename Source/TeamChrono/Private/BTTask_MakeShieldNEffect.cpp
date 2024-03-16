// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_MakeShieldNEffect.h"
#include "BaseEliteMonster.h"
#include "AIController.h"
#include <Blueprint/AIBlueprintHelperLibrary.h>
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_MakeShieldNEffect::UBTTask_MakeShieldNEffect(FObjectInitializer const& ObjectInitializer)
{
	NodeName = TEXT("Make Shield n Effect");
}

EBTNodeResult::Type UBTTask_MakeShieldNEffect::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto const* const cont = OwnerComp.GetAIOwner();
	auto* const EliteMonster = Cast<ABaseEliteMonster>(cont->GetPawn());

	if (EliteMonster)
	{
		//Make Shield & Effect
		EliteMonster->beforeGimic();

		//Set bool property in BB : 'isShieldOn' true
		UAIBlueprintHelperLibrary::GetAIController(EliteMonster)->GetBlackboardComponent()->SetValueAsBool("isShieldOn", true);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("MakeShieldNEffect Task has Cast Failed to EliteMonster!"))
	}


	return EBTNodeResult::Succeeded;
}