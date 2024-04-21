// Fill out your copyright notice in the Description page of Project Settings.


#include "Notify_Golem_FouthGimicEffect.h"
#include "BossAIController.h"
#include "Boss_Golem.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"

void UNotify_Golem_FouthGimicEffect::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp && MeshComp->GetOwner())
	{
		if (ABoss_Golem* const Boss = Cast<ABoss_Golem>(MeshComp->GetOwner()))
		{
			//Left Side Gimic Start
			if (Boss->GetFth_01_GimicStart() && !Boss->GetFth_02_GimicStart())
			{
				UE_LOG(LogTemp, Warning, TEXT("Left Effect On"));
				Boss->GetLeftEffect()->Activate();
			}
			//Right Side Gimic Start
			else if (Boss->GetFth_02_GimicStart() && Boss->GetFth_01_GimicStart())
			{
				UE_LOG(LogTemp, Warning, TEXT("Right Effect On"));
				Boss->GetRightEffect()->Activate();
			}
		}
	}
}
