// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "ComboAnimNotifyState.generated.h"

/**
 * 
 */
UCLASS()
class TEAMCHRONO_API UComboAnimNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()

	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

	UPROPERTY()
	class ATeamChronoCharacter* TeamChronoCharacter;
	
	UPROPERTY()
	class UABAnimInstance* ABAnimInstance;


};
