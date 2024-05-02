// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_ChronoLookPlayer.generated.h"

/**
 * 
 */
UCLASS()
class TEAMCHRONO_API UBTTask_ChronoLookPlayer : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTTask_ChronoLookPlayer();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	float GetRandomFloat(float min, float max);
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "LOOK TIME", meta = (AllowPrivateAccess = "true"))
	float minTime;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "LOOK TIME", meta = (AllowPrivateAccess = "true"))
	float maxTime;
};
