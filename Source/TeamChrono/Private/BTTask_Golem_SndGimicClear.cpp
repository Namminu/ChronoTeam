// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Golem_SndGimicClear.h"

UBTTask_Golem_SndGimicClear::UBTTask_Golem_SndGimicClear()
{
	NodeName = TEXT("Snd Gimic End");
}

EBTNodeResult::Type UBTTask_Golem_SndGimicClear::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return EBTNodeResult::Type();
}
