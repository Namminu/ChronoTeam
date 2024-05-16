// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_AfterChangePase.generated.h"

/**
 * 
 */
UCLASS()
class TEAMCHRONO_API UBTTask_AfterChangePase : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTTask_AfterChangePase();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "COLOR", meta = (AllowPrivateAccess = "true"))
	FColor Pase2Color;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "COLOR", meta = (AllowPrivateAccess = "true"))
	FColor Pase3Color;
};
