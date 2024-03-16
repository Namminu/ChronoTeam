// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_MakeShieldNEffect.generated.h"

/**
 * 
 */
UCLASS()
class TEAMCHRONO_API UBTTask_MakeShieldNEffect : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	explicit UBTTask_MakeShieldNEffect(FObjectInitializer const& ObjectInitializer);
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
private:
	//play anim to Pause delay
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PAUSE", meta = (AllowPrivateAccess = "true"))
	float delay;
};