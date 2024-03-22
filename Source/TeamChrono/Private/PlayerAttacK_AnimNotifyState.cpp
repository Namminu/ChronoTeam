// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAttacK_AnimNotifyState.h"
#include <TeamChrono/TeamChronoCharacter.h>

void UPlayerAttacK_AnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	//if (ABaseMonster* const monster = Cast<ABaseMonster>(MeshComp->GetOwner()))
	if (MeshComp && MeshComp->GetOwner())
	{
		if (ATeamChronoCharacter* const player = Cast<ATeamChronoCharacter>(MeshComp->GetOwner()))
		{
			UE_LOG(LogTemp, Warning, TEXT("Playe hits Start"));
			//player->GetAttackSwordBox()->SetNotifyRigidBodyCollision(true);
			//player->GetAttackSwordBox()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		}
	}
}

void UPlayerAttacK_AnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	//if (ABaseMonster* const monster = Cast<ABaseMonster>(MeshComp->GetOwner()))
	if (MeshComp && MeshComp->GetOwner())
	{
		if (ATeamChronoCharacter* const player = Cast<ATeamChronoCharacter>(MeshComp->GetOwner()))
		{
			UE_LOG(LogTemp, Warning, TEXT("Playe hits End"));
			//player->GetAttackSwordBox()->SetNotifyRigidBodyCollision(false);
			//player->GetAttackSwordBox()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		}
	}
}
