// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_Golem_FothGimic_GoMainBT.generated.h"

/**
 * 
 */
UCLASS()
class TEAMCHRONO_API UBTTask_Golem_FothGimic_GoMainBT : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTTask_Golem_FothGimic_GoMainBT();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
