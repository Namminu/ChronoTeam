// Fill out your copyright notice in the Description page of Project Settings.


#include "Notify_Chrono_LaunchClockPin.h"
#include "Boss_TimeMaster.h"
#include "Boss_Chrono_ShadowPartner.h"

void UNotify_Chrono_LaunchClockPin::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp && MeshComp->GetOwner())
	{
		if (MeshComp->GetOwner()->ActorHasTag("SHAPA"))
		{
			if (ABoss_Chrono_ShadowPartner* const Shapa = Cast<ABoss_Chrono_ShadowPartner>(MeshComp->GetOwner()))
			{
				Shapa->Shapa_LaunchPins();
			}
		}
		else
		{
			if (ABoss_TimeMaster* const Chrono = Cast<ABoss_TimeMaster>(MeshComp->GetOwner()))
			{
				Chrono->LaunchPins();
			}
		}
		
	}
}
