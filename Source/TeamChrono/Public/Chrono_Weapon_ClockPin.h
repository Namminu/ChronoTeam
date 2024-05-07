// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <GameFramework/ProjectileMovementComponent.h>
#include "Chrono_Weapon_ClockPin.generated.h"

UCLASS()
class TEAMCHRONO_API AChrono_Weapon_ClockPin : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AChrono_Weapon_ClockPin();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void RotateToPlayer();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void LaunchPin();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void BackToBossSocket();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void CalculateHitRange();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void ChangeOpacity();

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* RootScene;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* PinMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* ImplusePoint;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Z Force", meta = (AllowPrivateAccess = "true"))
	float Z_DownDegree;

};
