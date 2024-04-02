// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_SetCanTakeDamage.generated.h"

/**
 * 
 */
UCLASS()
class TEAMCHRONO_API UBTTask_SetCanTakeDamage : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	explicit UBTTask_SetCanTakeDamage(FObjectInitializer const& ObjectInitializer);
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TAKE DAMAGE", meta = (AllowPrivateAccess = "true"))
	bool isCanDamage;
};
