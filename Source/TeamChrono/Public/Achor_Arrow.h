// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <GameFramework/ProjectileMovementComponent.h>
#include "Achor_Arrow.generated.h"

UCLASS()
class TEAMCHRONO_API AAchor_Arrow : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AAchor_Arrow();

	//UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	//void DestoryByDistance(float distance);

	UFUNCTION()
	void OnAttackOverlapBegin(UPrimitiveComponent* const OverlappedComponent,
		AActor* const otherActor,
		UPrimitiveComponent* const OtherComponent,
		int const OtherBodyIndex,
		bool const FromSweep,
		FHitResult const& SweepResult);

	UFUNCTION()
	void OnAttackOverlapEnd(UPrimitiveComponent* const OverlappedComponent,
		AActor* const otherActor,
		UPrimitiveComponent* const OtherComponent,
		int const OtherBodyIndex);

	UFUNCTION(BlueprintCallable)
	void CallNiagaraEffect();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void arrowDestroy();

protected:
	// Called when the game starts or when spawned	
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	USceneComponent* Root;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "WEAPON", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Arrow;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "WEAPON", meta = (AllowPrivateAccess = "true"))
	class UCapsuleComponent* CollisionBox;

	UPROPERTY(EditAnywhere)
	UProjectileMovementComponent* ProjectileComponent;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UDamageType> DamageType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EFFECT", meta = (AllowPrivateAccess = "true"))
	class UNiagaraComponent* NiagaraEffect;

	float damageAmount;

	UPROPERTY(EditDefaultsOnly, Category = "EFFECT", meta = (AllowPrivateAccess = "true"))
	float delay;
};