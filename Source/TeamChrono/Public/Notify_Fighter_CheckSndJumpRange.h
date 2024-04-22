// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "Notify_Fighter_CheckSndJumpRange.generated.h"

/**
 * 
 */
UCLASS()
class TEAMCHRONO_API UNotify_Fighter_CheckSndJumpRange : public UAnimNotify
{
	GENERATED_BODY()
public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
