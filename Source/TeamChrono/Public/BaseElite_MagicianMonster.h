// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseEliteMonster.h"
#include <TeamChrono/TeamChronoCharacter.h>
#include "Magician_BigAttack.h"
#include "MonsterSpawner.h"
#include "BaseElite_MagicianMonster.generated.h"
/**
 * 
 */
UCLASS()
class TEAMCHRONO_API ABaseElite_MagicianMonster : public ABaseEliteMonster
{
	GENERATED_BODY()
	
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	ATeamChronoCharacter* player;

public:
	ABaseElite_MagicianMonster();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

/// Overlap Event Function 
	void OnAttackOverlapBegin(UPrimitiveComponent* const OverlappedComponent,
		AActor* const otherActor,
		UPrimitiveComponent* const OtherComponent,
		int const OtherBodyIndex,
		bool const FromSweep,
		FHitResult const& SweepResult) override;

	void OnAttackOverlapEnd(UPrimitiveComponent* const OverlappedComponent,
		AActor* const otherActor,
		UPrimitiveComponent* const OtherComponent,
		int const OtherBodyIndex) override;

	void OnRangeOverlapBegin(UPrimitiveComponent* const OverlappedComponent,
		AActor* const otherActor,
		UPrimitiveComponent* const OtherComponent,
		int const OtherBodyIndex,
		bool const FromSweep,
		FHitResult const& SweepResult) override;

	void OnRangeOverlapEnd(UPrimitiveComponent* const OverlappedComponent,
		AActor* const otherActor,
		UPrimitiveComponent* const OtherComponent,
		int const OtherBodyIndex) override;

	float TakeDamage(float DamageAmount,
		struct FDamageEvent const& DamageEvent,
		AController* EventInstigator,
		AActor* DamageCauser) override;

	UFUNCTION()
	void OnBigRangeOverlapBegin(UPrimitiveComponent* const OverlappedComponent,
		AActor* const otherActor,
		UPrimitiveComponent* const OtherComponent,
		int const OtherBodyIndex,
		bool const FromSweep,
		FHitResult const& SweepResult);

	UFUNCTION()
	void OnBigRangeOverlapEnd(UPrimitiveComponent* const OverlappedComponent,
		AActor* const otherActor,
		UPrimitiveComponent* const OtherComponent,
		int const OtherBodyIndex);

	int MeleeAttack_Implementation() override;

	//Shoot Magic Ball
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void SpawnMagicBall();

	//Make Big Attack
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void MakeBigAttack();

	UFUNCTION(BlueprintCallable)
	void SpawnMonster();

	void CreateMTI() override;

	void mon_Death() override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Collision, meta = (AllowPrivateAccess = "true"))
	USphereComponent* BigAttackRangeBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GIMIC ANIMATION", meta = (AllowPrivateAccess = "true"))
	UAnimMontage* Gimic_Montage2;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BIGACK", meta = (AllowPrivateAccess = "true"))
	bool isBigAck;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GIMIC", meta = (AllowPrivateAccess = "true"))
	TArray<AMonsterSpawner*> MonsterArray;

public:
/// Getter Func
	USphereComponent* GetBigAttackRange() const { return BigAttackRangeBox; }
};
