// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_Fighter_FothGimicMontage.generated.h"

/**
 * 
 */
UCLASS()
class TEAMCHRONO_API UBTTask_Fighter_FothGimicMontage : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTTask_Fighter_FothGimicMontage();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
