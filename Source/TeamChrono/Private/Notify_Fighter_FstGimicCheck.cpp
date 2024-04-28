// Fill out your copyright notice in the Description page of Project Settings.


#include "Notify_Fighter_FstGimicCheck.h"
#include "Boss_Fighter.h"

void UNotify_Fighter_FstGimicCheck::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp && MeshComp->GetOwner())
	{
		if (ABoss_Fighter* const Fighter = Cast<ABoss_Fighter>(MeshComp->GetOwner()))
		{
			// if Current Figther's Fst Gimic Attack Count over Max Count, Spawn Effect
			if (Fighter->GetFstAttackCount() >= Fighter->GetFstMaxCount())
			{
				//Spawn Marble
				Fighter->Fst_SpawnEffect();
				//Reset Fst Gimic Attack Count
				Fighter->SetFstAttackCount(0);

				if (Fighter->GetMarbleArray().Num() >= Fighter->GetFstMaxMarbleCount())
				{
					Fighter->FstGimic();
				}
			}
		}
	}
}
