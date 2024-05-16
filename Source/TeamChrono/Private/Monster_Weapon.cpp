// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster_Weapon.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AMonster_Weapon::AMonster_Weapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Weapon Setup
	Weapon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon"));
	SetRootComponent(Weapon);
	  
	//Actor Defaulf Setting
	SetActorEnableCollision(false);	//Can't Collision
	SetActorTickEnabled(false);

}

// Called when the game starts or when spawned
void AMonster_Weapon::BeginPlay()
{
	Super::BeginPlay();
	
	Change_Opacity(0, 1);
}

// Called every frame
void AMonster_Weapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMonster_Weapon::Wp_Death()
{	
	Weapon->SetSimulatePhysics(true);
	bool bIsSimulate = Weapon->IsSimulatingPhysics();
	UE_LOG(LogTemp, Error, TEXT("Weapon Simulate Physics : %s"), bIsSimulate);
	Change_Opacity(1, 0);

	FTimerHandle TimerHandle;
	float delay = 3.3f;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AMonster_Weapon::Wp_Destroy, delay, false);	//Destory Actor After DeathDelay
}

void AMonster_Weapon::Wp_Destroy()
{
	//Destroy();
}
