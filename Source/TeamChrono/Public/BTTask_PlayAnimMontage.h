// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BaseMonster.h"
#include "BTTask_PlayAnimMontage.generated.h"

/**
 * 
 */
UCLASS()
class TEAMCHRONO_API UBTTask_PlayAnimMontage : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	explicit UBTTask_PlayAnimMontage(FObjectInitializer const& ObjectInitializer);
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Montage", meta = (AllowPrivateAccess = "true"))
	UAnimMontage* AnimMontage;

	bool checkPlaying(ABaseMonster* const Monster);
};
