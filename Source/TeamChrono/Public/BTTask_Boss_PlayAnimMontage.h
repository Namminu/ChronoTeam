// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_Boss_PlayAnimMontage.generated.h"

/**
 * 
 */
UCLASS()
class TEAMCHRONO_API UBTTask_Boss_PlayAnimMontage : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	explicit UBTTask_Boss_PlayAnimMontage(FObjectInitializer const& ObjectInitializer);
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MONTAGE", meta = (AllowPrivateAccess = "true"))
	class UAnimMontage* Montage;

	bool checkPlaying(class ABase_Boss* const Boss);

	bool isMontagePlay = false;
};
