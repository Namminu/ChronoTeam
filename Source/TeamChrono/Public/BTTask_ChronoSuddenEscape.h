// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_ChronoSuddenEscape.generated.h"

/**
 * 
 */
UCLASS()
class TEAMCHRONO_API UBTTask_ChronoSuddenEscape : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTTask_ChronoSuddenEscape();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
