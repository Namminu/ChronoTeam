// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "PlayerHitDetectionNotify.generated.h"

/**
 * 
 */
UCLASS()
class TEAMCHRONO_API UPlayerHitDetectionNotify : public UAnimNotify
{
	GENERATED_BODY()
public:
	//void Received_Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference);

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
private:
	class ATeamChronoCharacter* Owner;
};
