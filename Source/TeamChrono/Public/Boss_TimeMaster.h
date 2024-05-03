// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base_Boss.h"
#include "Boss_TimeMaster.generated.h"

/**
 * 
 */
UCLASS()
class TEAMCHRONO_API ABoss_TimeMaster : public ABase_Boss
{
	GENERATED_BODY()
	
public:
	ABoss_TimeMaster();

protected:
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called when Actor Destroy
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
/// Chrono Local Func

	/// <summary>
	/// To Always Keep Distance from Player
	/// </summary>
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetFarfromPlayer(float distance, float newTime);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void StayLookPlayer(FVector TargetLocation, float newTime);

	/// <summary>
	/// Get Random Number to Attack&Gimic
	/// </summary>
	UFUNCTION(BlueprintCallable)
	int GetRandomAttackNum(int min, int max);

	UFUNCTION(BlueprintCallable)
	void SetFlashMT(class USkeletalMeshComponent* skeleton, int index);

	void CheckCurrentPase();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void OpenOtherBossPortal(int paseNum);

/// Override Funcs
	int MeleeAttack_Implementation() override;

	void Boss_Death_Implementation() override;

	//void InitFunc_Implementation() override;

	/// <summary>
	/// Chrono Attack Func
	/// 0 ~ 2 : Normal Attack
	/// 3 : Strike Attack
	/// </summary>
	void AttackFunc_Implementation(int caseNum) override;

	float TakeDamage(float DamageAmount,
		struct FDamageEvent const& DamageEvent,
		AController* EventInstigator,
		AActor* DamageCauser) override;

	void DamageFlash_Implementation() override;

/// Overlap Funcs
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

/// Calculate Funs



/// Attack Funcs
	// Normal Attack - Strike
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void StrikeAttack();

	// Gimic Attack Funcs
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void GimicFunc(int num);

	// Gimic Attack After Strike
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void StrikeGimic(int GimicNum);

private:
/// SKM
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SKM", meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* sk_Halo;

/// For Attack Properties
	// Flash MTI
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "DAMAGE FLASH", meta = (AllowPrivateAccess = "true"))
	class UMaterialInstanceDynamic* FlashMT;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "DAMAGE FLASH", meta = (AllowPrivateAccess = "true"))
	FLinearColor InitColor;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "DAMAGE FLASH", meta = (AllowPrivateAccess = "true"))
	float InitMultiplier;

	// Boss Pase Properties
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "DEFAULT", meta = (AllowPrivateAccess = "true"))
	int CurrentPase;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "PASE", meta = (AllowPrivateAccess = "true"))
	float f_2PaseHp;
	bool is2PaseStart;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "PASE", meta = (AllowPrivateAccess = "true"))
	float f_3PaseHp;
	bool is3PaseStart;

	// Default Properties
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "DEFAULT", meta = (AllowPrivateAccess = "true"))
	float DistanceToPlayer;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "DEFAULT", meta = (AllowPrivateAccess = "true"))
	bool bIsAttack;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "DEFAULT", meta = (AllowPrivateAccess = "true"))
	bool bIsGimic;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "DEFAULT", meta = (AllowPrivateAccess = "true"))
	int BossDamage;

	// Normal Attack Properties
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "NORMAL ATTACK", meta = (AllowPrivateAccess = "true"))
	int NormalAttackTotalCount;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "NORMAL ATTACK", meta = (AllowPrivateAccess = "true"))
	int cur_StrikeCount;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "NORMAL ATTACK", meta = (AllowPrivateAccess = "true"))
	int max_StrikeCount;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "NORMAL ATTACK", meta = (AllowPrivateAccess = "true"))
	int cur_SkillCount;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "NORMAL ATTACK", meta = (AllowPrivateAccess = "true"))
	int max_SkillCount;

	// Gimic Properties
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "GIMIC", meta = (AllowPrivateAccess = "true"))
	int GimicTotalCount;

public:
///Getter
	// Default 
	int GetBossPase() const { return CurrentPase; }
	int GetPlayerByDistance() const { return DistanceToPlayer; }

	// Normal Attack
	int GetNormalAtkType() const { return NormalAttackTotalCount; }

	// Gimic
	int GetGimicType() const { return GimicTotalCount; }

///Setter


};
