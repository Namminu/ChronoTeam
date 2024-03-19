// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_CheckBarrier.h"
#include "BaseEliteMonster.h"
#include "AIController.h"
#include <Blueprint/AIBlueprintHelperLibrary.h>
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_CheckBarrier::UBTTask_CheckBarrier(FObjectInitializer const& ObjectInitializer)
{
	NodeName = TEXT("Check Barrier Hp");
	bNotifyTick = true;
	barrierSuccess = false;
}

EBTNodeResult::Type UBTTask_CheckBarrier::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto const* const cont = OwnerComp.GetAIOwner();
	auto* const EliteMonster = Cast<ABaseEliteMonster>(cont->GetPawn());

	//현재 베리어 체력
	barrierHp = EliteMonster->GetBarrierHp();

	if (!barrierSuccess)
	{
		return EBTNodeResult::Failed;
	}
	else if (barrierSuccess)
	{
		UAIBlueprintHelperLibrary::GetAIController(EliteMonster)->GetBlackboardComponent()->SetValueAsBool("IsGimicClear", true);
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Type();
}

void UBTTask_CheckBarrier::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	if (barrierHp <= 0)
	{
		barrierSuccess = true;
	}
	else
	{
		barrierSuccess = false;
	}
}