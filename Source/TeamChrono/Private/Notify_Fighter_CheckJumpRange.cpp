// Fill out your copyright notice in the Description page of Project Settings.


#include "Notify_Fighter_CheckJumpRange.h"
#include "Boss_Fighter.h"

void UNotify_Fighter_CheckJumpRange::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp && MeshComp->GetOwner())
	{
		if (ABoss_Fighter* const Fighter = Cast<ABoss_Fighter>(MeshComp->GetOwner()))
		{
			Fighter->Calculate_JumpAttack();
		}
	}
}
