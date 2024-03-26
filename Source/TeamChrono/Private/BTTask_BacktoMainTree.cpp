// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_BacktoMainTree.h"
#include "BaseEliteMonster.h"
#include "AIController.h"
#include <Blueprint/AIBlueprintHelperLibrary.h>
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_BacktoMainTree::UBTTask_BacktoMainTree(FObjectInitializer const& ObjectInitializer)
{
	NodeName = TEXT("Back to MainTree");
}

EBTNodeResult::Type UBTTask_BacktoMainTree::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto const* const cont = OwnerComp.GetAIOwner();
	auto* const EliteMonster = Cast<ABaseEliteMonster>(cont->GetPawn());

	//initialize bool key
	UAIBlueprintHelperLibrary::GetAIController(EliteMonster)->GetBlackboardComponent()->SetValueAsBool("IsGimicClear", false);
	UAIBlueprintHelperLibrary::GetAIController(EliteMonster)->GetBlackboardComponent()->SetValueAsBool("IsShieldOn", false);
	UAIBlueprintHelperLibrary::GetAIController(EliteMonster)->GetBlackboardComponent()->SetValueAsBool("IsMontageEnd", false);
	//Back to Main tree to change bool key
	UAIBlueprintHelperLibrary::GetAIController(EliteMonster)->GetBlackboardComponent()->SetValueAsBool("IsGimic", false);
	return EBTNodeResult::Succeeded;
}
