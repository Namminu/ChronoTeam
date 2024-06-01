// Fill out your copyright notice in the Description page of Project Settings.


#include "FocusToPlayerAnimNotifyState.h"
#include "BaseMonster.h"
#include "Base_Boss.h"
#include <Kismet/GameplayStatics.h>
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "BossAIController.h"

void UFocusToPlayerAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	if (ABase_Boss* const Boss = Cast<ABase_Boss>(MeshComp->GetOwner()))
	{
		Boss->ResetSimpleMoveTo();
	}
}

void UFocusToPlayerAnimNotifyState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
	if (MeshComp && MeshComp->GetOwner())
	{
		if (ABaseMonster* const monster = Cast<ABaseMonster>(MeshComp->GetOwner()))
		{
			monster->FocusToPlayer();
		}
		else if (ABase_Boss* const Boss = Cast<ABase_Boss>(MeshComp->GetOwner()))
		{
			Boss->EyesOnPlayer();
		}
	}
}

void UFocusToPlayerAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (ABase_Boss* const Boss = Cast<ABase_Boss>(MeshComp->GetOwner()))
	{
		Boss->ResetSimpleMoveTo();
	}
}
