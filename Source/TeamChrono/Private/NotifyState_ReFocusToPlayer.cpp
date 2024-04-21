// Fill out your copyright notice in the Description page of Project Settings.


#include "NotifyState_ReFocusToPlayer.h"
#include "BossAIController.h"
#include "Base_Boss.h"
#include <Kismet/GameplayStatics.h>

void UNotifyState_ReFocusToPlayer::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	if (MeshComp && MeshComp->GetOwner())
	{
		ABase_Boss* const Boss = Cast<ABase_Boss>(MeshComp->GetOwner());
		if (Boss)
		{
			Boss->ClearFocusToPlayer();
			Boss->SetPlayerTargetLocation(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetActorLocation());
		}
	}
}

void UNotifyState_ReFocusToPlayer::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp && MeshComp->GetOwner())
	{
		ABase_Boss* const Boss = Cast<ABase_Boss>(MeshComp->GetOwner());
		if (Boss)
		{
			Boss->SetFocusToPlayer();
		}
	}
}
