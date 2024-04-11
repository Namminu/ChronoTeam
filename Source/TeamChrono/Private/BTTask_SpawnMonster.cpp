// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_SpawnMonster.h"
#include "BaseElite_MagicianMonster.h"
#include "AI_Controller_.h"

UBTTask_SpawnMonster::UBTTask_SpawnMonster(FObjectInitializer const& ObjectInitializer)
{
	NodeName = "Spawn Monster - Magician";
}

EBTNodeResult::Type UBTTask_SpawnMonster::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto const* const cont = OwnerComp.GetAIOwner();
	auto* const Magician = Cast<ABaseElite_MagicianMonster>(cont->GetPawn());

	if (Magician)
	{
		//Set Timer then Spawn Monster Code Work on BP_Magician
		Magician->SetGimicTimer();

		return EBTNodeResult::Succeeded;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("BTT_Spawn Monster : Cast Failed to Magician"));
		return EBTNodeResult::Failed;
	}
}
