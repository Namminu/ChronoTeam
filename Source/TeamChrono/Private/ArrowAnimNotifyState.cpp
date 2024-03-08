// Fill out your copyright notice in the Description page of Project Settings.


#include "ArrowAnimNotifyState.h"
#include "BaseMonster.h"

void UArrowAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	if (MeshComp && MeshComp->GetOwner() && MeshComp->GetOwner()->ActorHasTag("ACHOR"))
	{
		if (ABaseMonster* const monster = Cast<ABaseMonster>(MeshComp->GetOwner()))
		{
			monster->FireArrow();
		}
	}
}

void UArrowAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
}
