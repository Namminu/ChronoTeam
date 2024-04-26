// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterSpawner.h"
#include <NotifierDoor.h>

// Sets default values
AMonsterSpawner::AMonsterSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMonsterSpawner::BeginPlay()
{
	Super::BeginPlay();
	
	CurrentSpawn = 0;

	isMonsterDied = true;
	//MyDoor = ConnectDoor;
}

// Called every frame
void AMonsterSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsDoorConnect&& SpawnedMonster)
	{
		if (!SpawnedMonster->GetMonsterLive())
		{
			isMonsterDied = true;
			RemoveMonster();
			SpawnMonster_Implementation();
		}
	}
}

void AMonsterSpawner::SpawnMonster_Implementation()
{
	if (myMonster) 
	{
		if ((CurrentSpawn < SpawnCount) && isMonsterDied)
		{
			isMonsterDied = false;

			// 할당된 액터의 위치와 로테이션 가져오기
			FVector SpawnLocation = GetActorLocation();
			FRotator SpawnRotation = GetActorRotation();

			bool bNoCollisionFail = true;
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride =
				bNoCollisionFail ? ESpawnActorCollisionHandlingMethod::AlwaysSpawn : ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

			// 액터 스폰
			SpawnedMonster = GetWorld()->SpawnActor<ABaseMonster>(myMonster, SpawnLocation, SpawnRotation, ActorSpawnParams);

			if (IsDoorConnect)
			{
				AddMonster();
			}

			CurrentSpawn++;
		}
		else SetActorTickEnabled(false);

	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("There is no AssignedActor in 'myMonster'"));
	}
}

