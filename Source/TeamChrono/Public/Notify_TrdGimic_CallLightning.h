// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "Notify_TrdGimic_CallLightning.generated.h"

/**
 * 
 */
UCLASS()
class TEAMCHRONO_API UNotify_TrdGimic_CallLightning : public UAnimNotify
{
	GENERATED_BODY()
public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
