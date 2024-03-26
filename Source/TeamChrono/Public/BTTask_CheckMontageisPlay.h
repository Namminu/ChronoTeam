// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_CheckMontageisPlay.generated.h"

/**
 * 
 */
UCLASS()
class TEAMCHRONO_API UBTTask_CheckMontageisPlay : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	explicit UBTTask_CheckMontageisPlay(FObjectInitializer const& ObjectInitializer);
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
private:
	bool isPlaying;
};
