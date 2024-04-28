// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_Boss_JumpAttack.generated.h"

/**
 * 
 */
UCLASS()
class TEAMCHRONO_API UBTTask_Boss_JumpAttack : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTTask_Boss_JumpAttack();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
