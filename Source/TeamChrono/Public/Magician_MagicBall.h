// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <TeamChrono/TeamChronoCharacter.h>
#include <GameFramework/ProjectileMovementComponent.h>
#include "Magician_MagicBall.generated.h"

UCLASS()
class TEAMCHRONO_API AMagician_MagicBall : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMagician_MagicBall();

	UFUNCTION()
	void OnProjectileOverlapBegin(UPrimitiveComponent* const OverlappedComponent,
		AActor* const otherActor,
		UPrimitiveComponent* const OtherComponent,
		int const OtherBodyIndex,
		bool const FromSweep,
		FHitResult const& SweepResult);

	UFUNCTION()
	void OnProjectileOverlapEnd(UPrimitiveComponent* const OverlappedComponent,
		AActor* const otherActor,
		UPrimitiveComponent* const OtherComponent,
		int const OtherBodyIndex);

	float TakeDamage(float DamageAmount,
		struct FDamageEvent const& DamageEvent,
		AController* EventInstigator,
		AActor* DamageCauser) override;

	//플레이어 유도 기능 정의
	UFUNCTION()
	void ChasePlayer();

	/// <summary>
	/// 반탄력 기능 정의
	/// </summary>
	UFUNCTION(BlueprintCallable)
	void Re_Elasticity();
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetMagicSpeed(float newSpeed);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void HitNBurn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


private:
	//Projectile Size
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BALL", meta = (AllowPrivateAccess = "true"))
	class USphereComponent* Sphere;

	//Niagara Effectg - Projectile
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BALL", meta = (AllowPrivateAccess = "true"))
	class UNiagaraComponent* NiagaraEffect;

	//Projectile Component
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent* ProjectileComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	ATeamChronoCharacter* player;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UDamageType> DamageType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BALL", meta = (AllowPrivateAccess = "true"))
	float damageAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BALL", meta = (AllowPrivateAccess = "true"))
	float re_DamageAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BALL", meta = (AllowPrivateAccess = "true"))
	bool bisPlayerhit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BALL", meta = (AllowPrivateAccess = "true"))
	float re_Speed;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
