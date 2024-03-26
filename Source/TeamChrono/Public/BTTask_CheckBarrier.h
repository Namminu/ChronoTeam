// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_CheckBarrier.generated.h"

/**
 * 
 */
UCLASS()
class TEAMCHRONO_API UBTTask_CheckBarrier : public UBTTask_BlackboardBase
{
	GENERATED_BODY()	
public:
	explicit UBTTask_CheckBarrier(FObjectInitializer const& ObjectInitializer);
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
private:
	UPROPERTY()
	float barrierHp;

	bool barrierSuccess;
};
