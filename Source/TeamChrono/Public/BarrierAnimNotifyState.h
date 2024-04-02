// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "BaseElite_MagicianMonster.h"
#include "BarrierAnimNotifyState.generated.h"

/**
 * 
 */
UCLASS()
class TEAMCHRONO_API UBarrierAnimNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()
public:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MAGICIAN", meta = (AllowPrivateAccess = "true"))
	ABaseElite_MagicianMonster* Magician;

	UFUNCTION()
	void MagicianFunc();
};
