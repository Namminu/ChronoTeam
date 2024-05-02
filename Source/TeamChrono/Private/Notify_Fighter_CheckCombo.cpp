// Fill out your copyright notice in the Description page of Project Settings.


#include "Notify_Fighter_CheckCombo.h"
#include "BossAIController.h"
#include "Boss_Fighter.h"

void UNotify_Fighter_CheckCombo::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp && MeshComp->GetOwner())
	{
		if (ABoss_Fighter* const Fighter = Cast<ABoss_Fighter>(MeshComp->GetOwner()))
		{
			if (Fighter->GetComboCheck())
			{
				//1Ÿ���� 2Ÿ �Ѿ�� ����
				if (!Fighter->GetComboNumCheck())
				{
					//Snd Normal Attack
					Fighter->AttackFunc(1);
					Fighter->SetComboNum(true);
				}
				//2Ÿ���� 3Ÿ �Ѿ�� ����
				else if (Fighter->GetComboNumCheck())
				{
					//Trd Normal Attack
					Fighter->AttackFunc(3);
					Fighter->SetComboNum(false);
					Fighter->SetComboCheck(false);
				}
			}
		}
	}
}
