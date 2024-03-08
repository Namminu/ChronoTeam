// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_TestTask.h"

UBTTask_TestTask::UBTTask_TestTask(FObjectInitializer const& ObjectInitializer)
{
	NodeName = TEXT("Test Task");
}

EBTNodeResult::Type UBTTask_TestTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UE_LOG(LogTemp, Error, TEXT("This Sequence has Work"));

	return EBTNodeResult::Succeeded;
}

