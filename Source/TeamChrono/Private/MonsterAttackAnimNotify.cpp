// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterAttackAnimNotify.h"
#include "BaseMonster.h"

void UMonsterAttackAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp && MeshComp->GetOwner())
	{
		if (ABaseMonster* const monster = Cast<ABaseMonster>(MeshComp->GetOwner()))
		{
			monster->TempAttack();
			//monster->AttackStart();
			UE_LOG(LogTemp, Warning, TEXT("Attack Start"));
		}
	}
}