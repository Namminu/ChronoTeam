// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_RotateToPlayer.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_RotateToPlayer::UBTTask_RotateToPlayer(FObjectInitializer const& ObjectInitializer)
{
	NodeName = TEXT("Rotate To Player");
}

EBTNodeResult::Type UBTTask_RotateToPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BBc = OwnerComp.GetBlackboardComponent();
	if (BBc)
	{
		//Get BlackBoard Key : TargetLocation
		FVector playerLocation = BBc->GetValueAsVector(GetSelectedBlackboardKey());
		FVector currentLocation = OwnerComp.GetOwner()->GetActorLocation();

		//Get Vector to Target
		FVector targetDirection = playerLocation - currentLocation;
		targetDirection.Z = 0.f;

		//Calculate Rotation
		FRotator targetRotation = FRotationMatrix::MakeFromX(targetDirection).Rotator();

		FRotator currentRotation = OwnerComp.GetOwner()->GetActorRotation();

		//Lerp in to TargetRotation
		FRotator newRotation = FMath::RInterpTo(currentRotation, targetRotation, GetWorld()->GetDeltaSeconds(), RotationDelay);

		//Set AI Rotation
		//OwnerComp.GetOwner()->SetActorRotation(newRotation);
		OwnerComp.GetOwner()->SetActorRotation(targetRotation);

		return EBTNodeResult::Succeeded;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Rotate Player : Get BlackBoard Failed"));
		return EBTNodeResult::Failed;
	}

	return EBTNodeResult::Type();
}
