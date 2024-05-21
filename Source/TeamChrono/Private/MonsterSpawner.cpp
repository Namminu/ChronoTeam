// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterSpawner.h"
#include <NotifierDoor.h>
#include "Monster_Weapon.h"

// Sets default values
AMonsterSpawner::AMonsterSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AMonsterSpawner::DestroySpawnedMonster()
{
	SpawnedMonster->Destroy();
	SpawnedMonster->GetWeaponInstance_Fst()->Destroy();
}

// Called when the game starts or when spawned
void AMonsterSpawner::BeginPlay()
{
	Super::BeginPlay();
	
	CurrentSpawn = 0;

	isMonsterDied = true;
	isAllMonsterDie = false;
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

			if (CurrentSpawn < SpawnCount)
			{
				//Destory Actor After DeathDelay
				FTimerHandle TimerHandle;
				float delay = 1.f;
				GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AMonsterSpawner::SpawnMonster_Implementation, delay, false);
			}
			else
			{
				isAllMonsterDie = true;
				SetActorTickEnabled(false);
			}
		}
	}
}

void AMonsterSpawner::InitFunc_Implementation()
{
	CurrentSpawn = 0;

	isMonsterDied = true;
	isAllMonsterDie = false;

	//if (SpawnedMonster)
	//{
	//	SpawnedMonster->Temp_InitFunc();
	//}

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

	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("There is no AssignedActor in 'myMonster'"));
	}
}

