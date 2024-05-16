// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MonsterArrow.generated.h"

UCLASS()
class TEAMCHRONO_API AMonsterArrow : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMonsterArrow();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnAttackOverlapBegin(UPrimitiveComponent* const OverlappedComponent,
		AActor* const otherActor,
		UPrimitiveComponent* const OtherComponent,
		int const OtherBodyIndex,
		bool const FromSweep,
		FHitResult const& SweepResult);

	UFUNCTION(BlueprintCallable)
	void CallNiagaraEffect();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void ArrowDestroy();

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "COMPO", meta = (AllowPrivateAccess = "true"))
	class UNiagaraComponent* ArrowShape;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "COMPO", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* CollBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "COMPO", meta = (AllowPrivateAccess = "true"))
	class UNiagaraComponent* HitEffect;

	UPROPERTY(EditAnywhere)
	class UProjectileMovementComponent* ProjectileComponent;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UDamageType> DamageType;

	UPROPERTY(EditDefaultsOnly, Category = "ATTACK", meta = (AllowPrivateAccess = "true"))
	float delay;
};
