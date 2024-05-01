// Fill out your copyright notice in the Description page of Project Settings.


#include "Notify_Fighter_ChangeMarble.h"
#include "Boss_Fighter.h"
#include "Fighter_Fst_Marble.h"

void UNotify_Fighter_ChangeMarble::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp && MeshComp->GetOwner())
	{
		if (ABoss_Fighter* const Fighter = Cast<ABoss_Fighter>(MeshComp->GetOwner()))
		{
			Fighter->Fst_MarbleChange();
		}
	}
}