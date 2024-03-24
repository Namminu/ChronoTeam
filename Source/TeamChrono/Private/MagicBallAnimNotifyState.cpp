// Fill out your copyright notice in the Description page of Project Settings.


#include "MagicBallAnimNotifyState.h"
#include "BaseElite_MagicianMonster.h"

void UMagicBallAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	if (MeshComp && MeshComp->GetOwner() && MeshComp->GetOwner()->ActorHasTag("MAGICIAN"))
	{
		if (ABaseElite_MagicianMonster* const Magician = Cast<ABaseElite_MagicianMonster>(MeshComp->GetOwner()))
		{
			Magician->SpawnMagicBall();
		}
	}
}

void UMagicBallAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
}
