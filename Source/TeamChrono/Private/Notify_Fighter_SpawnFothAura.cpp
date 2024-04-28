// Fill out your copyright notice in the Description page of Project Settings.


#include "Notify_Fighter_SpawnFothAura.h"
#include "Boss_Fighter.h"

void UNotify_Fighter_SpawnFothAura::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp && MeshComp->GetOwner())
	{
		if (ABoss_Fighter* const Fighter = Cast<ABoss_Fighter>(MeshComp->GetOwner()))
		{
			Fighter->FothGimicSpawnAuraAttack();
		}
	}
}
