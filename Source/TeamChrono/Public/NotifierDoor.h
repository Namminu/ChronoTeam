// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MonsterSpawner.h"
#include "BaseMonster.h"
#include "NotifierDoor.generated.h"

UCLASS()
class TEAMCHRONO_API ANotifierDoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANotifierDoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void SetOpenDoor();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void SetCloseDoor();

	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
		class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner", meta = (AllowPrivateAccess = "true"))
	TArray<AMonsterSpawner*> SpawnerArray;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Spawner", meta = (AllowPrivateAccess = "true"))
	TArray<ABaseMonster*> MonsterArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* RootScene;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* BoxColl;

	bool isGetWorked;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class ADoorNextDoor* NextDoor;

public:
	TArray<class AMonsterSpawner*> GetSpawnerArray() const { return SpawnerArray; }
	TArray<class ABaseMonster*> GetMonsterArray() const { return MonsterArray; }
};
