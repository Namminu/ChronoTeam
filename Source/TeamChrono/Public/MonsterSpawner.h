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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Monster", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<ABaseMonster> myMonster;
	//ABaseMonster* myMonster;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//몬스터 생성 함수
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "MonsterSpawn")
	void SpawnMonster();

	TSubclassOf<ABaseMonster> GetMyMonster() const { return myMonster; }

};
