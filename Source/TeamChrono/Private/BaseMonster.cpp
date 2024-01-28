// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseMonster.h"

// Sets default values
ABaseMonster::ABaseMonster()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseMonster::BeginPlay()
{
	Super::BeginPlay();

	//시작 시 애니메이션 재생
	Creating();	//일어서는 애니메이션
	if (MontageHasFinished())	//Creating 이 종료된 경우
	{
		Shouting();	//포효 애니메이션 재생
	}
}

// Called every frame
void ABaseMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseMonster::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

int ABaseMonster::MeleeAttack_Implementation()
{
	if (AtkMontage)
	{
		PlayAnimMontage(AtkMontage);
	}
	return 0;
}

int ABaseMonster::Creating_Implementation()
{
	if (CreateMontage)
	{
		PlayAnimMontage(CreateMontage);
	}
	return 0;
}

int ABaseMonster::Shouting_Implementation()
{
	if (ShoutingMontage)
	{
		PlayAnimMontage(ShoutingMontage);
	}
	return 0;
}

UAnimMontage* ABaseMonster::GetAtkMontage() const
{ 
	return AtkMontage; 
}

UBehaviorTree* ABaseMonster::GetBehaviorTree() const
{ 
	return BTree;
}

bool ABaseMonster::MontageHasFinished()
{
	return GetMesh()->GetAnimInstance()->Montage_GetIsStopped(GetCreateMontage());
}

UAnimMontage* ABaseMonster::GetCreateMontage() const
{
	return CreateMontage;
}