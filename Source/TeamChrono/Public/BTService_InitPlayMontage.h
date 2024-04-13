// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_InitPlayMontage.generated.h"

/**
 * 
 */
UCLASS()
class TEAMCHRONO_API UBTService_InitPlayMontage : public UBTService_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTService_InitPlayMontage();
	void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
