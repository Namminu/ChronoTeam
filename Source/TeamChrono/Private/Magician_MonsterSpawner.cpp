// Fill out your copyright notice in the Description page of Project Settings.


#include "Magician_MonsterSpawner.h"

void AMagician_MonsterSpawner::SpawnMonster_Implementation()
{
	if (GetMyMonster())
	{
		// �Ҵ�� ������ ��ġ�� �����̼� ��������
		FVector SpawnLocation = GetActorLocation();
		FRotator SpawnRotation = GetActorRotation();

		// ���� ����
		ABaseMonster* SpawnedMonster = GetWorld()->SpawnActor<ABaseMonster>(GetMyMonster(), SpawnLocation, SpawnRotation);
		SpawnedMonster->Tags.Add("GETSPAWNED");
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("There is no AssignedActor in 'myMonster'"));
	}
}
