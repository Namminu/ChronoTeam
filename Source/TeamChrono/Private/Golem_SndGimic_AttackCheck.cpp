// Fill out your copyright notice in the Description page of Project Settings.


#include "Golem_SndGimic_AttackCheck.h"
#include "BossAIController.h"
#include "Boss_Golem.h"

void UGolem_SndGimic_AttackCheck::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp && MeshComp->GetOwner())
	{
		if (ABoss_Golem* const Golem = Cast<ABoss_Golem>(MeshComp->GetOwner()))
		{
			Golem->Calculate_SndGimicAttackRange();
		}
	}
}
