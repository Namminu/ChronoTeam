// Fill out your copyright notice in the Description page of Project Settings.


#include "NotifyState_ChronoLaserAttack.h"
#include "Boss_TimeMaster.h"
#include "Boss_Chrono_ShadowPartner.h"

void UNotifyState_ChronoLaserAttack::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	if (MeshComp && MeshComp->GetOwner())
	{
		if (ABoss_TimeMaster* const Chrono = Cast<ABoss_TimeMaster>(MeshComp->GetOwner()))
		{
			Chrono->SetLaserAttackTimer();
		}
		else if (ABoss_Chrono_ShadowPartner* const Shapa = Cast<ABoss_Chrono_ShadowPartner>(MeshComp->GetOwner()))
		{
			Shapa->Shapa_LaserAttack();
		}
	}
}

void UNotifyState_ChronoLaserAttack::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp && MeshComp->GetOwner())
	{
		if (ABoss_TimeMaster* const Chrono = Cast<ABoss_TimeMaster>(MeshComp->GetOwner()))
		{
			Chrono->ClearLaserTimer();
		}
		else if (ABoss_Chrono_ShadowPartner* const Shapa = Cast<ABoss_Chrono_ShadowPartner>(MeshComp->GetOwner()))
		{
			Shapa->Shapa_ClearLaserAttack();
		}
	}
}
