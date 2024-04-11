// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHitDetectionNotify.h"
#include <TeamChrono/TeamChronoCharacter.h>

void UPlayerHitDetectionNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Owner = Cast<ATeamChronoCharacter>(MeshComp->GetOwner());
	if (Owner != nullptr)
	{
		Owner->HitDetect();
	}
}
