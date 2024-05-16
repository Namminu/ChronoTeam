// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include <TeamChrono/TeamChronoCharacter.h>
#include "NotifyState_Chrono_StayFocus.generated.h"

/**
 * 
 */
UCLASS()
class TEAMCHRONO_API UNotifyState_Chrono_StayFocus : public UAnimNotifyState
{
	GENERATED_BODY()
public:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime) override;
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PLAYER", meta = (AllowPrivateAccess = "true"))
	ATeamChronoCharacter* player;
};
