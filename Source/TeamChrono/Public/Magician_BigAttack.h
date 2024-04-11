// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
//#include <TeamChrono/TeamChronoCharacter.h>
#include "Magician_BigAttack.generated.h"

UCLASS()
class TEAMCHRONO_API AMagician_BigAttack : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMagician_BigAttack();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void MakeSword();

	UFUNCTION(BlueprintCallable)
	void ActivateEffect(UBoxComponent* hitbox, UNiagaraComponent* Sword);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void AttackFinally();

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

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void DetachFromPlayer();

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	USceneComponent* Root;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Collision, meta = (AllowPrivateAccess = "true"))
	class UCapsuleComponent* Capsule;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "EFFECT", meta = (AllowPrivateAccess = "true"))
	class UNiagaraComponent* FloorEffect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Collision, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* SwordHitBox1;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "EFFECT", meta = (AllowPrivateAccess = "true"))
	class UNiagaraComponent* SwordEffect1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Collision, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* SwordHitBox2;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "EFFECT", meta = (AllowPrivateAccess = "true"))
	class UNiagaraComponent* SwordEffect2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Collision, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* SwordHitBox3;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "EFFECT", meta = (AllowPrivateAccess = "true"))
	class UNiagaraComponent* SwordEffect3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Collision, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* SwordHitBox4;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "EFFECT", meta = (AllowPrivateAccess = "true"))
	class UNiagaraComponent* SwordEffect4;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Collision, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* SwordHitBox;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "EFFECT", meta = (AllowPrivateAccess = "true"))
	class UNiagaraComponent* SwordEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "EFFECT", meta = (AllowPrivateAccess = "true"))
	class UNiagaraComponent* HitEffect;

	UPROPERTY()
	float damageAmount;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UDamageType> DamageType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "EFFECT", meta = (AllowPrivateAccess = "true"))
	float destroyDelay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EFFECT", meta = (AllowPrivateAccess = "true"))
	float swordDelay;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "EFFECT", meta = (AllowPrivateAccess = "true"))
	TArray<UBoxComponent*> HitBoxes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EFFECT", meta = (AllowPrivateAccess = "true"))
	bool isSwordReady;

public:
	UCapsuleComponent* GetCapsule() const { return Capsule; }

	UBoxComponent* GetSwordBox() const { return SwordHitBox; }
}; 