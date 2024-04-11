// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackAnimNotifyState.h"
#include "BaseMonster.h"

void UAttackAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	if (MeshComp && MeshComp->GetOwner())
	{
		if (ABaseMonster* const monster = Cast<ABaseMonster>(MeshComp->GetOwner()))
		{
			monster->TempAttack();
			//monster->AttackStart();
			//UE_LOG(LogTemp, Warning, TEXT("Attack Start"));
		}
	}
}

void UAttackAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp && MeshComp->GetOwner())
	{
		if (ABaseMonster* const monster = Cast<ABaseMonster>(MeshComp->GetOwner()))
		{
			//monster->AttackEnd();
			UE_LOG(LogTemp, Warning, TEXT("Attack End"));
		}
	}
}
