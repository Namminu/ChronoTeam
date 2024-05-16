// Fill out your copyright notice in the Description page of Project Settings.


#include "Notify_Chrono_BossUpDown.h"
#include "Boss_TimeMaster.h"
#include "Boss_Chrono_ShadowPartner.h"

void UNotify_Chrono_BossUpDown::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp && MeshComp->GetOwner())
	{
		if (ABoss_TimeMaster* const Chrono = Cast<ABoss_TimeMaster>(MeshComp->GetOwner()))
		{
			Chrono->SetBossUpOrDown(IsDown);
		}
		else if (ABoss_Chrono_ShadowPartner* const Shapa = Cast<ABoss_Chrono_ShadowPartner>(MeshComp->GetOwner()))
		{
			Shapa->SetShapaUpOrDown(IsDown);
		}
	}
}
