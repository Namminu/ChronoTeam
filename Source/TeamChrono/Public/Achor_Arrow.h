// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Achor_Arrow.generated.h"

UCLASS()
class TEAMCHRONO_API AAchor_Arrow : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAchor_Arrow();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void LaunchForward(float distance);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "WEAPON", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Arrow;
};
