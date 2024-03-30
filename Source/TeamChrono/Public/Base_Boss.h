// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CombatInterface.h"
#include "Base_Boss.generated.h"

UCLASS()
class TEAMCHRONO_API ABase_Boss : public ACharacter, public ICombatInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABase_Boss();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/// <summary>
	/// Attack Algorithm Func
	/// </summary>
	int MeleeAttack_Implementation() override;

	/// <summary>
	/// Setup Flash Material Instance for Damage Flash
	/// </summary>
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void SetFlashMTI();

	/// <summary>
	/// Damage Flash Func Called When Boss Hitted
	/// </summary>
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void DamageFlash();

	/// <summary>
	/// Func When BossMonster Died Call
	/// </summary>
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Boss_Death();

	/// <summary>
	/// Take Damage Func
	/// </summary>
	float TakeDamage(float DamageAmount,
		struct FDamageEvent const& DamageEvent,
		AController* EventInstigator,
		AActor* DamageCauser) override;

	/// <summary>
	/// Weapon Range Overlap Begin Event
	/// </summary>
	UFUNCTION()
	virtual void OnAttackOverlapBegin(UPrimitiveComponent* const OverlappedComponent,
		AActor* const otherActor,
		UPrimitiveComponent* const OtherComponent,
		int const OtherBodyIndex,
		bool const FromSweep,
		FHitResult const& SweepResult);

	/// <summary>
	/// Weapon Range Overlap End Event
	/// </summary>
	UFUNCTION()
	virtual void OnAttackOverlapEnd(UPrimitiveComponent* const OverlappedComponent,
		AActor* const otherActor,
		UPrimitiveComponent* const OtherComponent,
		int const OtherBodyIndex);

	/// <summary>
	/// Attack Range Collision OverlapBegin Event
	/// </summary>
	UFUNCTION()
	virtual void OnRangeOverlapBegin(UPrimitiveComponent* const OverlappedComponent,
		AActor* const otherActor,
		UPrimitiveComponent* const OtherComponent,
		int const OtherBodyIndex,
		bool const FromSweep,
		FHitResult const& SweepResult);

	/// <summary>
	/// Attack Range Collision OverlapEnd Event
	/// </summary>
	UFUNCTION()
	virtual void OnRangeOverlapEnd(UPrimitiveComponent* const OverlappedComponent,
		AActor* const otherActor,
		UPrimitiveComponent* const OtherComponent,
		int const OtherBodyIndex);

private:
///Components
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "COMPO", meta = (AllowPrivateAccess = "true"))
	class USphereComponent* AttackRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "COMPO", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* WeaponRange;


///Montage
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MONTAGE", meta = (AllowPrivateAccess = "true"))
	UAnimMontage* DeathMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MONTAGE", meta = (AllowPrivateAccess = "true"))
	UAnimMontage* CreateMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MONTAGE", meta = (AllowPrivateAccess = "true"))
	UAnimMontage* NormalAttackMontage;

///Properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MONSTER", meta = (AllowPrivateAccess = "true"))
	float f_bossMaxHp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MONSTER", meta = (AllowPrivateAccess = "true"))
	float f_bossCurrentHp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MONSTER", meta = (AllowPrivateAccess = "true"))
	float f_bossAtk;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MONSTER", meta = (AllowPrivateAccess = "true"))
	float f_bossSpeed;

/// Materials
	UPROPERTY()
	UMaterialInstanceDynamic* Fst_FlashMT;

///Arraies
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DAMAGE FLASH", meta = (AllowPrivateAccess = "true"))
	TArray<UMaterialInstanceDynamic*> MTIArray;

public:
///Getter
	float GetBossMaxHp() const { return f_bossMaxHp; }
	float GetBossCurrentHp() const { return f_bossCurrentHp; }
	float GetBossAtkMount() const { return f_bossAtk; }

	TArray<UMaterialInstanceDynamic*> GetMTIArray() const { return MTIArray; }

///Setter
	void SetBossAtkMount(const float newMount) { f_bossAtk = newMount; }
	void SetBossCurrentHp(const float newHp) { f_bossCurrentHp = newHp; }
};
