// Fill out your copyright notice in the Description page of Project Settings.


#include "BossAttackCheckAnimNotify.h"
#include "Base_Boss.h"

void UBossAttackCheckAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp && MeshComp->GetOwner())
	{
		if (ABase_Boss* const Boss = Cast<ABase_Boss>(MeshComp->GetOwner()))
		{
			//Boss->RotateToPlayer();
			Boss->CheckComboAttackCando();
			UE_LOG(LogTemp, Warning, TEXT("Check Combo State"));
		}
	}
}
