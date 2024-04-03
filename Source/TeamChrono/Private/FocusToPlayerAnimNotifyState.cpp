// Fill out your copyright notice in the Description page of Project Settings.


#include "FocusToPlayerAnimNotifyState.h"
#include "BaseMonster.h"
#include <Kismet/GameplayStatics.h>


void UFocusToPlayerAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	//Get Player Location
	//player = Cast<ATeamChronoChacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	//playerLocation = player->GetActorLocation();

	if (MeshComp && MeshComp->GetOwner())
	{
		if (ABaseMonster* const monster = Cast<ABaseMonster>(MeshComp->GetOwner()))
		{
			monster->GetActorLocation();
		}
	}
}

void UFocusToPlayerAnimNotifyState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{

}

void UFocusToPlayerAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp && MeshComp->GetOwner())
	{
		if (ABaseMonster* const monster = Cast<ABaseMonster>(MeshComp->GetOwner()))
		{
			monster->FocusToPlayer(false);
		}
	}
}
