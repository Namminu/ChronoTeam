// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_InitSelectKey.generated.h"

/**
 * 
 */
UCLASS()
class TEAMCHRONO_API UBTService_InitSelectKey : public UBTService_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTService_InitSelectKey();
	void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "INIT", meta = (AllowPrivateAccess = "true"))
	bool SelectBool;
};