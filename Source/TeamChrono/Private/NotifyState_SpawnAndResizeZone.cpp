// Fill out your copyright notice in the Description page of Project Settings.


#include "NotifyState_SpawnAndResizeZone.h"
#include "Boss_TimeMaster.h"

void UNotifyState_SpawnAndResizeZone::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	if (MeshComp && MeshComp->GetOwner())
	{
		if (ABoss_TimeMaster* const Chrono = Cast<ABoss_TimeMaster>(MeshComp->GetOwner()))
		{
			Chrono->StartPlayerSlow();
		}
	}
}

void UNotifyState_SpawnAndResizeZone::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp && MeshComp->GetOwner())
	{
		if (ABoss_TimeMaster* const Chrono = Cast<ABoss_TimeMaster>(MeshComp->GetOwner()))
		{
			Chrono->ResizePlayerSlow();
		}
	}
}
