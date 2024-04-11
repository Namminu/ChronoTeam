// Fill out your copyright notice in the Description page of Project Settings.


#include "CommanderBigAttackAnimNotify.h"
#include "BaseEliteMonster.h"

void UCommanderBigAttackAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp && MeshComp->GetOwner())
	{
		if (ABaseEliteMonster* const EliteMonster = Cast<ABaseEliteMonster>(MeshComp->GetOwner()))
		{
			EliteMonster->TempBigAttack();
		}
	}
}
