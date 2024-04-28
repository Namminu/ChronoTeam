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
	//Spawner 가 생성할 몬스터 변수 - BP에서 정할 수 있도록 함
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MONSTER", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<ABaseMonster> myMonster;
	//ABaseMonster* myMonster;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class ABaseMonster* SpawnedMonster;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//몬스터 생성 함수
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "MonsterSpawn")
	void SpawnMonster();

	UFUNCTION(BlueprintImplementableEvent)
	void AddMonster();
	UFUNCTION(BlueprintImplementableEvent)
	void RemoveMonster();
	UFUNCTION(BlueprintImplementableEvent)
	void RemoveSelf();


	TSubclassOf<ABaseMonster> GetMyMonster() const { return myMonster; }

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MONSTER", meta = (AllowPrivateAccess = "true"))
	int SpawnCount;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "MONSTER", meta = (AllowPrivateAccess = "true"))
	int CurrentSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MONSTER", meta = (AllowPrivateAccess = "true"))
	bool IsDoorConnect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MONSTER", meta = (EditCondition = "IsDoorConnect", AllowPrivateAccess = "true"))
	class ANotifierDoor* ConnectDoor;

	bool isMonsterDied;

	class ANotifierDoor* MyDoor;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool isAllMonsterDie;

public:
	UFUNCTION(BlueprintCallable)
	bool GetAllMonsterDie() const { return isAllMonsterDie; }
};
