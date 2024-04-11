// Fill out your copyright notice in the Description page of Project Settings.


#include "Notify_GolemTrdGimicAttackCheck.h"
#include "Boss_Golem.h"

void UNotify_GolemTrdGimicAttackCheck::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp && MeshComp->GetOwner())
	{
		if (ABoss_Golem* const Boss = Cast<ABoss_Golem>(MeshComp->GetOwner()))
		{
			Boss->Calculate_TrdGimicAttackRange();
		}
	}
}
