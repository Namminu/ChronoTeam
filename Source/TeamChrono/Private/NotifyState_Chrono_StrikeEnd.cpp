// Fill out your copyright notice in the Description page of Project Settings.


#include "NotifyState_Chrono_StrikeEnd.h"
#include "Boss_TimeMaster.h"

void UNotifyState_Chrono_StrikeEnd::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	if (MeshComp && MeshComp->GetOwner())
	{
		if (ABoss_TimeMaster* const Chrono = Cast<ABoss_TimeMaster>(MeshComp->GetOwner()))
		{
			Chrono->Strike_AddNiagaraEffect(NiaEffect);

			Chrono->SetActorHiddenInGame(false);

			Chrono->SetActorLocation(
				FVector(Chrono->GetCenterArrow()->GetActorLocation().X, Chrono->GetCenterArrow()->GetActorLocation().Y, UpAmount));
		
			Chrono->Strike_AttackLine();
		}
	}
}

void UNotifyState_Chrono_StrikeEnd::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp && MeshComp->GetOwner())
	{
		if (ABoss_TimeMaster* const Chrono = Cast<ABoss_TimeMaster>(MeshComp->GetOwner()))
		{
			Chrono->CalculateStrikeHitRange();
		}
	}
}
