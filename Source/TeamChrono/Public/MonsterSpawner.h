// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseMonster.h"
#include "MonsterSpawner.generated.h"

UCLASS()
class TEAMCHRONO_API AMonsterSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMonsterSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	//Spawner �� ������ ���� ���� - BP���� ���� �� �ֵ��� ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Monster", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<ABaseMonster> myMonster;
	//ABaseMonster* myMonster;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//���� ���� �Լ�
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "MonsterSpawn")
	void SpawnMonster();

	TSubclassOf<ABaseMonster> GetMyMonster() const { return myMonster; }

};
