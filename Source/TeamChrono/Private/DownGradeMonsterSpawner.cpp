// Fill out your copyright notice in the Description page of Project Settings.


#include "DownGradeMonsterSpawner.h"

// Sets default values
ADownGradeMonsterSpawner::ADownGradeMonsterSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ADownGradeMonsterSpawner::MonsterSpawn_Implementation()
{
	if (myMonster)
	{
		// �Ҵ�� ������ ��ġ�� �����̼� ��������
		FVector SpawnLocation = GetActorLocation();
		FRotator SpawnRotation = GetActorRotation();

		bool bNoCollisionFail = true;
		FActorSpawnParameters ActorSpawnParams;
		ActorSpawnParams.SpawnCollisionHandlingOverride =
			bNoCollisionFail ? ESpawnActorCollisionHandlingMethod::AlwaysSpawn : ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

		// ���� ����
		SpawnedMonster = GetWorld()->SpawnActor<ABaseMonster>(myMonster, SpawnLocation, SpawnRotation, ActorSpawnParams);
	}
}

// Called when the game starts or when spawned
void ADownGradeMonsterSpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADownGradeMonsterSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

