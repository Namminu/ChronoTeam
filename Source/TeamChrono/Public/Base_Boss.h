// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CombatInterface.h"
#include "BehaviorTree/BehaviorTree.h"
#include <TeamChrono/TeamChronoCharacter.h>
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

	void SetFocusToPlayer();
	void ClearFocusToPlayer();

	UFUNCTION()
	void PlayMontage(UAnimMontage* Montage);

	/// <summary>
	/// Rotate to Player Func When Befor Combo Attack
	/// </summary>
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void RotateToPlayer();

	/// <summary>
	/// Check Boss to Can do Combo Attack
	/// </summary>
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void CheckComboAttackCando();

	/// <summary>
	/// Setup Flash Material Instance for Damage Flash
	/// </summary>
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SetFlashMTIArray(UMaterialInstanceDynamic* MT);

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

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void UpdateHpPercent();

	/// <summary>
	/// Damage Flash When Monster Hitted
	/// </summary>
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void DamageFlash();

	/// <summary>
	/// Attack Range Collision OverlapBegin Event
	/// / Bind in Base Boss
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
	/// / Bind in Base Boss
	/// </summary>
	UFUNCTION()
	virtual void OnRangeOverlapEnd(UPrimitiveComponent* const OverlappedComponent,
		AActor* const otherActor,
		UPrimitiveComponent* const OtherComponent,
		int const OtherBodyIndex);

private:
///Boss Name
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BOSS", meta = (AllowPrivateAccess = "true"))
	FName n_BossName;

///Behavior Tree
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	UBehaviorTree* BTree;

///Cast to Player
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PLAYER", meta = (AllowPrivateAccess = "true"))
	ATeamChronoCharacter* player;

///Components
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "COMPO", meta = (AllowPrivateAccess = "true"))
	class USphereComponent* AttackRange;

///Montage
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MONTAGE", meta = (AllowPrivateAccess = "true"))
	UAnimMontage* DeathMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MONTAGE", meta = (AllowPrivateAccess = "true"))
	UAnimMontage* NormalAttackMontage;

///Properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MONSTER", meta = (AllowPrivateAccess = "true"))
	bool bisInvincible;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MONSTER", meta = (AllowPrivateAccess = "true"))
	float f_bossMaxHp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MONSTER", meta = (AllowPrivateAccess = "true"))
	float f_bossCurrentHp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MONSTER", meta = (AllowPrivateAccess = "true"))
	float f_bossAtk;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MONSTER", meta = (AllowPrivateAccess = "true"))
	float f_bossInitSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PLAYER", meta = (AllowPrivateAccess = "true"))
	FVector playerLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MONTAGE", meta = (AllowPrivateAccess = "true"))
	bool bIsMontageEnd;

///DamageTypes
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UDamageType> DamageType;

/// Materials
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DAMAGE FLASH", meta = (AllowPrivateAccess = "true"))
	UMaterialInstanceDynamic* Fst_FlashMT;

///Arraies
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DAMAGE FLASH", meta = (AllowPrivateAccess = "true"))
	TArray<UMaterialInstanceDynamic*> MTIArray;

public:
///Getter
	float GetBossMaxHp() const { return f_bossMaxHp; }
	float GetBossCurrentHp() const { return f_bossCurrentHp; }
	float GetBossAtkMount() const { return f_bossAtk; }
	float GetBossInitSpeed() const { return f_bossInitSpeed; }
	bool GetInvincible() const { return bisInvincible; }
	bool GetMontageEnd() const { return bIsMontageEnd; }

	UFUNCTION(BlueprintCallable)
	FVector GetPlayerTargetLocation() const { return playerLocation; }

	TArray<UMaterialInstanceDynamic*> GetMTIArray() const { return MTIArray; }
	UMaterialInstanceDynamic* GetFstMTI() const { return Fst_FlashMT; }

	TSubclassOf<UDamageType> GetDamageType() const { return DamageType; }

	ATeamChronoCharacter* GetPlayerProperty() const { return player; }

	UBehaviorTree* GetBehaviorTree() const { return BTree; }

	class USphereComponent* GetAttackRangeColl() const { return AttackRange; }

	FName GetBossName() const { return n_BossName; }

///Setter
	void SetBossAtkMount(const float newMount) { f_bossAtk = newMount; }
	void SetBossCurrentHp(const float newHp) { f_bossCurrentHp = newHp; }
	void SetInvincible(const bool newBool) { bisInvincible = newBool; }
	void SetMontageEnd(const bool newBool) { bIsMontageEnd = newBool; }

	void SetFstMTI(UMaterialInstanceDynamic* MTI) { Fst_FlashMT = MTI; }

	UFUNCTION(BlueprintCallable)
	void SetPlayerTargetLocation(const FVector newLocation) { playerLocation = newLocation; }

	void SetBossName(const FName newName) { n_BossName = newName; }
};