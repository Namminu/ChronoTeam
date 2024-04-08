// Fill out your copyright notice in the Description page of Project Settings.


#include "Notify_GolemCheckThirdGimicCount.h"
#include "Boss_Golem.h"

void UNotify_GolemCheckThirdGimicCount::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp && MeshComp->GetOwner())
	{
		if (ABoss_Golem* const Boss = Cast<ABoss_Golem>(MeshComp->GetOwner()))
		{
			if (Boss->GetGolemCurrentAttackCount() >= Boss->GetGolemMaxAttackCount())
			{			
				Boss->TrdGimic();
				UE_LOG(LogTemp, Error, TEXT("Golem Third Gimic Called by Notify"));
			}
		}
	}
}
