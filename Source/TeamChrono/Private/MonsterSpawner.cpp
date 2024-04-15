// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterSpawner.h"

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
	
	//임시용 몬스터 생성 확인
	//SpawnMonster();
}

// Called every frame
void AMonsterSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMonsterSpawner::SpawnMonster_Implementation()
{
	if (myMonster) 
	{
		// 할당된 액터의 위치와 로테이션 가져오기
		FVector SpawnLocation = GetActorLocation();
		FRotator SpawnRotation = GetActorRotation();

		bool bNoCollisionFail = true;
		FActorSpawnParameters ActorSpawnParams;
		ActorSpawnParams.SpawnCollisionHandlingOverride =
			bNoCollisionFail ? ESpawnActorCollisionHandlingMethod::AlwaysSpawn : ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

		// 액터 스폰
		ABaseMonster* SpawnedMonster = GetWorld()->SpawnActor<ABaseMonster>(myMonster, SpawnLocation, SpawnRotation, ActorSpawnParams);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("There is no AssignedActor in 'myMonster'"));
	}
}

