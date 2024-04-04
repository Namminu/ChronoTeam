// Fill out your copyright notice in the Description page of Project Settings.


#include "ArrowAnimNotifyState.h"
#include "BaseMonster.h"
#include <Kismet/GameplayStatics.h>
#include "AI_Controller_.h"
#include <ComboAnimNotifyState.h>
#include <TeamChrono/TeamChronoCharacter.h>

void UArrowAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	if (MeshComp && MeshComp->GetOwner() && MeshComp->GetOwner()->ActorHasTag("ACHOR"))
	{
		monster = Cast<ABaseMonster>(MeshComp->GetOwner());
		if (monster)
		{
			monster->FireArrow();
		}
	}
}

void UArrowAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
}
