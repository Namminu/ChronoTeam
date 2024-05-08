// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "NotifyState_Chrono_StrikeEnd.generated.h"

/**
 * 
 */
UCLASS()
class TEAMCHRONO_API UNotifyState_Chrono_StrikeEnd : public UAnimNotifyState
{
	GENERATED_BODY()
public:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Up Amount", meta = (AllowPrivateAccess = "true"))
	float UpAmount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NIA EFFECT", meta = (AllowPrivateAccess = "true"))
	class UNiagaraComponent* NiaEffect;
};
