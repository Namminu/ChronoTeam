// Fill out your copyright notice in the Description page of Project Settings.


#include "Magician_MonsterSpawner.h"

void AMagician_MonsterSpawner::SpawnMonster_Implementation()
{
	if (GetMyMonster())
	{
		// 할당된 액터의 위치와 로테이션 가져오기
		FVector SpawnLocation = GetActorLocation();
		FRotator SpawnRotation = GetActorRotation();

		// 액터 스폰
		ABaseMonster* SpawnedMonster = GetWorld()->SpawnActor<ABaseMonster>(GetMyMonster(), SpawnLocation, SpawnRotation);
		SpawnedMonster->Tags.Add("GETSPAWNED");
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("There is no AssignedActor in 'myMonster'"));
	}
}
