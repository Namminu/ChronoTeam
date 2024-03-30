// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveAnimNotifyState.h"


UMoveAnimNotifyState::UMoveAnimNotifyState()
{
	MoveDistancePerSec = 0;
	TotalTime = 0;
}

void UMoveAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{

	Owner = MeshComp->GetOwner();
	if (Owner != nullptr)
	{
		StartLocation = Owner->GetActorLocation();
		TotalDistance = TotalDuration * MoveDistancePerSec; // 전체 이동 거리
		// Begin 부터 End 까지 걸리는 시간이 TotalDuration 으로 넘어온다
		TotalTime = TotalDuration;

		Owner->GetWorld()->GetTimerManager().ClearTimer(MoveTimerHandle);
		Owner->GetWorld()->GetTimerManager().SetTimer(MoveTimerHandle,
			FTimerDelegate::CreateLambda([this]()-> void
				{
					if (Owner != nullptr)
					{
						FVector TargetLocation = FVector(StartLocation.X, StartLocation.Y, Owner->GetActorLocation().Z) + Owner->GetActorForwardVector() * TotalDistance;
						Owner->SetActorLocation(TargetLocation, true);
					}
				}
			)
			, TotalDuration
					, false
					);
	}
}

void UMoveAnimNotifyState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
	if (Owner != nullptr)    
	{
		if (Owner->GetWorld()->GetTimerManager().IsTimerActive(MoveTimerHandle))
		{
			float ElapsedTime = Owner->GetWorld()->GetTimerManager().GetTimerElapsed(MoveTimerHandle);
			float Ratio = ElapsedTime / TotalTime;

			FVector TargetLocation = FVector(StartLocation.X, StartLocation.Y, Owner->GetActorLocation().Z) + Owner->GetActorForwardVector() * Ratio * TotalDistance;

			Owner->SetActorLocation(TargetLocation, true);
		}
	}
}

void UMoveAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
}