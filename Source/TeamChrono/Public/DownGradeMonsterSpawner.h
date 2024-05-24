// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseMonster.h"
#include "DownGradeMonsterSpawner.generated.h"

UCLASS()
class TEAMCHRONO_API ADownGradeMonsterSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADownGradeMonsterSpawner();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void MonsterSpawn();

	UFUNCTION(BlueprintCallable)
	void SpawnMonsterDestroy();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void InitFunc();

	UFUNCTION(BlueprintCallable)
	void ResetInSequence();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void BindMonsterDieEvent();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MONSTER", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<ABaseMonster> myMonster;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class ABaseMonster* SpawnedMonster;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TArray<ABaseMonster*> SpawnMosnterArray;
};
