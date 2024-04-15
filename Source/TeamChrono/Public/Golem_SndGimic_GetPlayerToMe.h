// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "Golem_SndGimic_GetPlayerToMe.generated.h"

/**
 * 
 */
UCLASS()
class TEAMCHRONO_API UGolem_SndGimic_GetPlayerToMe : public UAnimNotify
{
	GENERATED_BODY()
public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
