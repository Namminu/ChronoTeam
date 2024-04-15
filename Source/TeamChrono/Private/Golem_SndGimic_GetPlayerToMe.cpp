// Fill out your copyright notice in the Description page of Project Settings.


#include "Golem_SndGimic_GetPlayerToMe.h"
#include "Boss_Golem.h"

void UGolem_SndGimic_GetPlayerToMe::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp && MeshComp->GetOwner())
	{
		if (ABoss_Golem* const Golem = Cast<ABoss_Golem>(MeshComp->GetOwner()))
		{
			UE_LOG(LogTemp, Warning, TEXT("Notify Called : Golem Get Player to Me"));

			Golem->SetPlayerToMe();
		}
	}
}