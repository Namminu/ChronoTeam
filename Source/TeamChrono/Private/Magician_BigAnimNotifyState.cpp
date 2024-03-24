// Fill out your copyright notice in the Description page of Project Settings.


#include "Magician_BigAnimNotifyState.h"
#include "BaseElite_MagicianMonster.h"
#include <Kismet/GameplayStatics.h>
#include <TeamChrono/TeamChronoCharacter.h>

void UMagician_BigAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	if (MeshComp && MeshComp->GetOwner() && MeshComp->GetOwner()->ActorHasTag("MAGICIAN"))
	{
		if (ABaseElite_MagicianMonster* const Magician = Cast<ABaseElite_MagicianMonster>(MeshComp->GetOwner()))
		{		
			ATeamChronoCharacter* player = Cast<ATeamChronoCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
			Magician->MakeBigAttack(player);
		}
	}
}

void UMagician_BigAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
}
