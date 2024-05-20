// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelTransferVolume.generated.h"

UCLASS()
class TEAMCHRONO_API ALevelTransferVolume : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALevelTransferVolume();

	//UFUNCTION()
	//void NotifyActorBeginOverlap(AActor* OtherActor) override;

	UFUNCTION()
	virtual void OnCollisionOverlapBegin(UPrimitiveComponent* const OverlappedComponent,
		AActor* const otherActor,
		UPrimitiveComponent* const OtherComponent,
		int const OtherBodyIndex,
		bool const FromSweep,
		FHitResult const& SweepResult);

	void ChangeLevel();

	UFUNCTION(BlueprintImplementableEvent)
	void FadeOut();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LEVEL", meta = (AllowPrivateAccess = "true"))
	FName TransferLevelName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* TransferVolume;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WIDGET", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> FadeWZ;
};
