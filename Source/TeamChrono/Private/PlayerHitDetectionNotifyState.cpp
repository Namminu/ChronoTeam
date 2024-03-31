// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHitDetectionNotifyState.h"
#include <TeamChrono/TeamChronoCharacter.h>

void UPlayerHitDetectionNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Owner = Cast<ATeamChronoCharacter>(MeshComp->GetOwner());
		
}

void UPlayerHitDetectionNotifyState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
	if (Owner != nullptr)
	{
		Owner->HitDetect();
	}
}

void UPlayerHitDetectionNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
}
