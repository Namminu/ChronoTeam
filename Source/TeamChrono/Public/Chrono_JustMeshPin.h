// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Chrono_JustMeshPin.generated.h"

UCLASS()
class TEAMCHRONO_API AChrono_JustMeshPin : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AChrono_JustMeshPin();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void ChangeOpacity();

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "COMPONENT", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* PinMesh;

public:
	UStaticMeshComponent* GetMesh() const { return PinMesh; }
};
