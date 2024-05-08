// Fill out your copyright notice in the Description page of Project Settings.


#include "Notify_Chrono_StrikeFrontOpacity.h"
#include "Boss_TimeMaster.h"

void UNotify_Chrono_StrikeFrontOpacity::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp && MeshComp->GetOwner())
	{
		if (ABoss_TimeMaster* const Chrono = Cast<ABoss_TimeMaster>(MeshComp->GetOwner()))
		{
			Chrono->Strike_AddNiagaraEffect(NiaEffect);
		}
	}
}
