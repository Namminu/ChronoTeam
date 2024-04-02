// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/StaticMeshActor.h"
#include "RenderVolume.generated.h"

UCLASS()
class TEAMCHRONO_API ARenderVolume : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ARenderVolume();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void NotifyActorBeginOverlap(AActor* OtherActor) override;

	UFUNCTION()
	void NotifyActorEndOverlap(AActor* OtherActor) override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RENDER BOX", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* collider;

	UPROPERTY(VisibleAnywhere)
	TArray<AActor*> OverlappingActors;

	UPROPERTY(VisibleAnywhere)
	TArray<AStaticMeshActor*> OverlappingMeshs;
};
