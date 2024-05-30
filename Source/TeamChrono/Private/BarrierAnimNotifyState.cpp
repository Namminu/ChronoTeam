// Fill out your copyright notice in the Description page of Project Settings.


#include "BarrierAnimNotifyState.h"

void UBarrierAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	if (MeshComp && MeshComp->GetOwner() && MeshComp->GetOwner()->ActorHasTag("MAGICIAN"))
	{
		Magician = Cast<ABaseElite_MagicianMonster>(MeshComp->GetOwner());
		if (Magician)
		{
			//Set Properties
			Magician->SetInvincible(true);
			//Magician->SetIsMontage(true);
			//Call BarrierFunc
			Magician->beforeGimic();
			Magician->ReNewBarrierHp();
		}
		else UE_LOG(LogTemp, Warning, TEXT("Barrier Anim : Magician Cast Failed"));
	}
}

void UBarrierAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (Magician)
	{
		Magician->SetIsMontage(false);
	}
}

void UBarrierAnimNotifyState::MagicianFunc()
{
	if (Magician)
	{

	}
}