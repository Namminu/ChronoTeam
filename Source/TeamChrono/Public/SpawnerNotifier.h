// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "MonsterSpawner.h"
#include "SpawnerNotifier.generated.h"

UCLASS()
class TEAMCHRONO_API ASpawnerNotifier : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnerNotifier();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* CollisionBox;	

	//신호를 보낼 Spawner 배열 -> 에디터에서 할당할 수 있도록
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SetSpawner", meta = (AllowPrivateAccess = "true"))
	TArray<AMonsterSpawner*> SpawnerArray;

	//1회용성 작동을 위한 bool 변수
	bool isGetWorked = false;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
