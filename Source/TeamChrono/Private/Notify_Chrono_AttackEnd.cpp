// Fill out your copyright notice in the Description page of Project Settings.


#include "Notify_Chrono_AttackEnd.h"
#include "Boss_TimeMaster.h"
#include "Boss_Chrono_ShadowPartner.h"
#include "BehaviorTree/BlackboardComponent.h"

void UNotify_Chrono_AttackEnd::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp && MeshComp->GetOwner())
	{
		if (ABoss_TimeMaster* const Chrono = Cast<ABoss_TimeMaster>(MeshComp->GetOwner()))
		{
			Chrono->AttackEnd();
		}
		else if (ABoss_Chrono_ShadowPartner* const Shapa = Cast<ABoss_Chrono_ShadowPartner>(MeshComp->GetOwner()))
		{
			Shapa->Shapa_AttackEnd();
		}
	}
}
