// Fill out your copyright notice in the Description page of Project Settings.


#include "NotifyState_Chrono_StayFocus.h"
#include "Boss_Chrono_ShadowPartner.h"
#include "Boss_TimeMaster.h"
#include <Kismet/GameplayStatics.h>

void UNotifyState_Chrono_StayFocus::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	//Cast to Player
	player = Cast<ATeamChronoCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}

void UNotifyState_Chrono_StayFocus::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
	if (MeshComp && MeshComp->GetOwner())
	{
		if (ABoss_TimeMaster* const Chrono = Cast<ABoss_TimeMaster>(MeshComp->GetOwner()))
		{
			//UE_LOG(LogTemp, Error, TEXT("Cast Success"));
			Chrono->StayLookPlayer(player->GetActorLocation(), 0.1f);
		}
		else if (ABoss_Chrono_ShadowPartner* const Shapa = Cast<ABoss_Chrono_ShadowPartner>(MeshComp->GetOwner()))
		{
			Shapa->StayLookPlayer(player->GetActorLocation(), 0.1f);
		}
	}
}
