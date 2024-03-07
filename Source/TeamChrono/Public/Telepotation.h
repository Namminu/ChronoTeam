// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Telepotation.generated.h"

UCLASS()
class TEAMCHRONO_API ATelepotation : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATelepotation();

	UFUNCTION()
	void Teleport(AActor* actor);

	UFUNCTION()
	void NotifyActorBeginOverlap(AActor* OtherActor) override;

	UFUNCTION(BlueprintImplementableEvent)
	void FadeIn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY()
	USceneComponent* Root;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TELEPORT", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* collider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TELEPORT", meta = (AllowPrivateAccess = "true"))
	class UArrowComponent* arrowTarget;

};
