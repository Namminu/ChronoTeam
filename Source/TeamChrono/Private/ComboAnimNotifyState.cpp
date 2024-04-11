// Fill out your copyright notice in the Description page of Project Settings.


#include "ComboAnimNotifyState.h"
#include <TeamChrono/TeamChronoCharacter.h>
#include "ABAnimInstance.h"

void UComboAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{

    if (MeshComp && MeshComp->GetOwner())
    {
        TeamChronoCharacter = Cast<ATeamChronoCharacter>(MeshComp->GetOwner());
        if (TeamChronoCharacter)
        {
            ABAnimInstance = Cast<UABAnimInstance>(TeamChronoCharacter->GetMesh()->GetAnimInstance());
        }
    }


}
void UComboAnimNotifyState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{

    if (TeamChronoCharacter)
    {
        if (TeamChronoCharacter->IsComboInputOn || TeamChronoCharacter->IsComboPushOn)
        {
            ABAnimInstance->NextAttackCheck();
        }
    }
    
}

void UComboAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{

}