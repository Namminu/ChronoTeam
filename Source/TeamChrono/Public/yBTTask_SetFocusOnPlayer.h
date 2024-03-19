// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "yBTTask_SetFocusOnPlayer.generated.h"

/**
 * 
 */
UCLASS()
class TEAMCHRONO_API UyBTTask_SetFocusOnPlayer : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	explicit UyBTTask_SetFocusOnPlayer(FObjectInitializer const& ObjectInitializer);
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
