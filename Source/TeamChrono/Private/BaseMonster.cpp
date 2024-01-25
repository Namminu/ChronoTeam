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

UBehaviorTree* ABaseMonster::GetBehaviorTree() const
{
	return BTree;
}

UAnimMontage* ABaseMonster::GetMontage() const
{
	return Montage;
}

int ABaseMonster::MeleeAttack_Implementation()
{
	if (Montage)
	{
		PlayAnimMontage(Montage);
	}
	return 0;
}

