// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base_Boss.h"
#include "Boss_Golem.generated.h"

/**
 * 
 */
UCLASS()
class TEAMCHRONO_API ABoss_Golem : public ABase_Boss
{
	GENERATED_BODY()
public:
	ABoss_Golem();

protected:
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called when Actor Destroy
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
// Override Functions
	int MeleeAttack_Implementation() override;

	void Boss_Death_Implementation() override;

	float TakeDamage(float DamageAmount,
		struct FDamageEvent const& DamageEvent,
		AController* EventInstigator,
		AActor* DamageCauser) override;

// Golem Functions

	/// <summary>
	/// Golem Normal Attack Func
	/// 0 : First Normal Attack
	/// 1 : Second Normal Combo Attack
	/// 2 : Second Big Combo Attack
	/// 3 : Third Gimic Attack
	/// </summary>
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void AttackFunc(int caseNum);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void SetJumpAttackLocation();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void SetFstGimicTimer(float SpawnDelay);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void ClearFstGimicTimer();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SndGimicJumpToCenter();

	UFUNCTION()
	void Golem_Destroy();

// Overlap Events
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

// Calculate Attack Range Func
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void Calculate_FstAttackRange();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void Calculate_SndAttackRange();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void Calculate_SndBigAttackRange();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void Calculate_SndGimicAttackRange();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void Calculate_TrdGimicAttackRange();

// Gimic Functions	
	/// <summary>
	/// 패턴 1 : 제자리 함성 후 낙석주의 / 체력기반
	/// </summary>
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void FstGimic();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void StartFstGimicTimer();

	/// <summary>
	/// 패턴 2 : 중앙 점프 후 끌당 / 시간기반
	/// </summary>
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SndGimic();

	/// <summary>
	/// Set Timer to Start Snd Gimic
	/// </summary>
	void SetSndGimicTimer();

	/// <summary>
	/// 패턴 3 : 추격 후 바닥찍기 / 기본공격 4회마다
	/// </summary>
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void TrdGimic();

	/// <summary>
	/// 패턴 4 : 부위파괴 2번(왼, 오) / 체력기반, 2번 실행
	/// </summary>
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void FothGimic();

private:
///Set Gimic Start Hp Percent
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GIMIC_Fst", meta = (AllowPrivateAccess = "true"))
	float FstGimic_StartHp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GIMIC_Foth", meta = (AllowPrivateAccess = "true"))
	float FothGimic_01_StartHp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GIMIC_Foth", meta = (AllowPrivateAccess = "true"))
	float FothGimic_02_StartHp;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "GIMIC_SND", meta = (AllowPrivateAccess = "true"))
	float SndGimicDelay;

///Properties to Gimic Start
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ATTACK COUNT", meta = (AllowPrivateAccess = "true"))
	float MaxAtkCount;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ATTACK COUNT", meta = (AllowPrivateAccess = "true"))
	float CurrentAtkCount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ATTACK COUNT", meta = (AllowPrivateAccess = "true"))
	bool isTrdGimicNow;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ATTACK BIG", meta = (AllowPrivateAccess = "true"))
	float distanceToPlayer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ATTACK BIG", meta = (AllowPrivateAccess = "true"))
	bool isJump;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GIMIC_TRD", meta = (AllowPrivateAccess = "true"))
	bool isTrdGimicCanAttack;

	//Check Gimic is Started
	FTimerHandle SndGimicTimerHandle;

	//Fst Gimic Properties
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GIMIC_FST", meta = (AllowPrivateAccess = "true"))
	bool isFst_GimicStart;
	UPROPERTY()
	bool isFst_GimicIng;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GIMIC_FST", meta = (AllowPrivateAccess = "true"))
	float FstGimicTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GIMIC_FST", meta = (AllowPrivateAccess = "true"))
	FVector RockSpawnLocation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GIMIC_FST", meta = (AllowPrivateAccess = "true"))
	float RockSpawnDelay;

	//Snd Gimic Properties
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "GIMIC_SND", meta = (AllowPrivateAccess = "true"))
	class AActor* TargetArrowDirection;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "GIMIC_SND", meta = (AllowPrivateAccess = "true"))
	bool isSnd_JumpCenterIng;


	//Fouth Gimic Properties
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GIMIC_FOTH", meta = (AllowPrivateAccess = "true"))
	bool isFoth01_GimicStart;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GIMIC_FOTH", meta = (AllowPrivateAccess = "true"))
	bool isFoth02_GimicStart;
	
///AnimMontage
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MONTAGE", meta = (AllowPrivateAccess = "true"))
	UAnimMontage* SecondAttackMontage;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MONTAGE", meta = (AllowPrivateAccess = "true"))
	UAnimMontage* BigAttackMontage;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MONTAGE", meta = (AllowPrivateAccess = "true"))
	UAnimMontage* HittedMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MONTAGE", meta = (AllowPrivateAccess = "true"))
	UAnimMontage* TrdGimicAttackMontage;

/// Niagara Effects
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "EFFECT", meta = (AllowPrivateAccess = "true"))
	class UNiagaraComponent* L_PartsBreakEffect;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "EFFECT", meta = (AllowPrivateAccess = "true"))
	class UNiagaraComponent* R_PartsBreakEffect;


public:
///Getter
	float GetGolemCurrentAttackCount() const { return CurrentAtkCount; }
	float GetGolemMaxAttackCount() const { return MaxAtkCount; }

	bool GetFstGimicIng() const { return isFst_GimicIng; }
	bool GetSndJumping() const { return isSnd_JumpCenterIng; }

///Setter
	UFUNCTION(BlueprintCallable)
	void SetGolemCurrentAttackCount(const float newCount) { CurrentAtkCount = newCount; }
	UFUNCTION(BlueprintCallable)
	void SetFstGimicing(const bool newBool) { isFst_GimicIng = newBool; }
	UFUNCTION(BlueprintCallable)
	void SetSndJumping(const bool newBool) { isSnd_JumpCenterIng = newBool; }
};