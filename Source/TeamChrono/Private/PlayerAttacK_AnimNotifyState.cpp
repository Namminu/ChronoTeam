// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAttacK_AnimNotifyState.h"
#include <TeamChrono/TeamChronoCharacter.h>
#include "Components/BoxComponent.h"

void UPlayerAttacK_AnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	//if (ABaseMonster* const monster = Cast<ABaseMonster>(MeshComp->GetOwner()))
	if (MeshComp && MeshComp->GetOwner())
	{
		if (ATeamChronoCharacter* const player = Cast<ATeamChronoCharacter>(MeshComp->GetOwner()))
		{
			//player->GetAttackSwordBox()->SetCollisionProfileName("Player Sword Box");
			player->GetAttackSwordBox()->SetNotifyRigidBodyCollision(true);
			player->GetAttackSwordBox()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

			UE_LOG(LogTemp, Warning, TEXT("Playe hits Start"));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("AttackAnim : player Cast Failed"));
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
			//player->GetAttackSwordBox()->SetCollisionProfileName("Player Sword Box");
			player->GetAttackSwordBox()->SetNotifyRigidBodyCollision(false);
			player->GetAttackSwordBox()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

			UE_LOG(LogTemp, Warning, TEXT("Playe hits End"));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("AttackAnim : player Cast Failed"));
		}
	}
}
