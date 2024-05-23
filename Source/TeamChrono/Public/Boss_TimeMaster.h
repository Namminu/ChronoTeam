// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base_Boss.h"
#include "Chrono_Weapon_ClockPin.h"
#include "Chrono_JustMeshPin.h"
#include "DownGradeMonsterSpawner.h"
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
	UFUNCTION(BlueprintCallable)
	void CheckStateFunc();

	/// <summary>
	/// To Always Keep Distance from Player
	/// 거리 유지하도록 만들려고 했다가 공전으로 이동하면서 안쓰는 함수
	/// 추후 완성 시까지 사용하지 않으면 삭제
	/// </summary>
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetFarfromPlayer(float distance, float newTime);
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void SuddenEscapeFromPlayer();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void StayLookPlayer(FVector TargetLocation, float newTime);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void SetLocationToOrbit(FVector TargetLocation);

	/// <summary>
	/// Get Random Number to Attack&Gimic
	/// </summary>
	UFUNCTION(BlueprintCallable)
	int GetRandomAttackNum(int min, int max);

	UFUNCTION(BlueprintCallable)
	void SetFlashMT(class USkeletalMeshComponent* skeleton, int index);

	void CheckCurrentPase();
	void CheckSpawnHpRate();
	void CheckOpenTimeDelayZone();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void OpenOtherBossPortal(int paseNum);
	
	//UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	//void StartPlayerSlow(float slowRate, float slowDuration);
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void StartPlayerSlow();
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void ResizePlayerSlow();

	UFUNCTION(BlueprintImplementableEvent)
	void Boss2PaseAttachPin();
	UFUNCTION(BlueprintImplementableEvent)
	void Boss3PaseAttachPin();

	UFUNCTION(BlueprintCallable)
	void TempAttachPin(TSubclassOf<AChrono_JustMeshPin> Weapon, FName WeaponSocket);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void ChangeHaloColor(FColor newColor);

	UFUNCTION(BlueprintCallable)
	void ChangeMoveOrbitDirection();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void StartChronoEndSequence();

	UFUNCTION(BlueprintCallable)
	void DestroyAllChrono();

	UFUNCTION(BlueprintCallable)
	void ResetSpawner();

/// Override Funcs
	int MeleeAttack_Implementation() override;

	void Boss_Death_Implementation() override;

	void InitFunc_Implementation(FVector FirstLocation) override;

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
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void CalculateStrikeHitRange();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void CalculateLaserAttackRange();

/// Attack Funcs
	/// <summary>
	/// Almost Called By Notify
	/// </summary>
	UFUNCTION(BlueprintCallable)
	void AttackEnd();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void LaunchPins();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void SpawnDash();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void SetLaserAttackTimer();
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void ClearLaserTimer();
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void SetBossUpOrDown(const bool isDown);


	// About Timer Funcs
	UFUNCTION(BlueprintCallable)
	void SetAttackTimer();
	UFUNCTION(BlueprintCallable)
	void ResetAttackTimer();
	UFUNCTION(BlueprintCallable)
	void CallAttackBB();

/// Normal Attack - Strike
	// Call Montage Func
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void StrikeAttack();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void Strike_FrontFunc();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void Strike_AttackLine();	

	// Gimic Attack Funcs
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void GimicFunc(int num);

	// Gimic Attack After Strike
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void StrikeGimic();

/// Gimic Attack Funcs
	// Fst Gimic - Spawn Monster by Hp Rate
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void SpawnMonsterFlip();

	// Snd Gimic - Spawn Meteor Random Space
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void SpawnMeteor(int currentPase);

	// Trd Gimic - Spawn GroundOrb 
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void SpawnGroundOrb();

	// Foth Gimic - Spawn ShadowPartner
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void ShadowPartner();

private:
/// Center Arrow
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default", meta = (AllowPrivateAccess = "true"))
	class AActor* CenterArrow;

/// SKM
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SKM", meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* sk_Halo;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Component", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* ArrowCollBox;

/// Weapon
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	TArray<AChrono_JustMeshPin*> ClockPinArray;

	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	//TArray<AChrono_Weapon_ClockPin*> ClockPinWeapon;

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
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PASE", meta = (AllowPrivateAccess = "true"))
	class UMaterialInstanceDynamic* HaloMTI;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PASE", meta = (AllowPrivateAccess = "true"))
	FColor Pase2Color;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PASE", meta = (AllowPrivateAccess = "true"))
	FColor Pase3Color;

	// Default Properties
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "DEFAULT", meta = (AllowPrivateAccess = "true"))
	float DistanceToCenter;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "DEFAULT", meta = (AllowPrivateAccess = "true"))
	float fRotateSpeed;

	bool IsEscape;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MOVE", meta = (AllowPrivateAccess = "true"))
	bool bIsOrbitING;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MOVE", meta = (AllowPrivateAccess = "true"))
	float NormalPC;

	// Normal Attack Properties
	FTimerHandle AttackTimer;
	int BeforeAttackNum;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ATTACK", meta = (AllowPrivateAccess = "true"))
	float AttackDelay;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "NORMAL ATTACK", meta = (AllowPrivateAccess = "true"))
	int NormalAttackTotalCount = 3;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "NORMAL ATTACK", meta = (AllowPrivateAccess = "true"))
	int cur_StrikeCount;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "NORMAL ATTACK", meta = (AllowPrivateAccess = "true"))
	int max_StrikeCount;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "NORMAL ATTACK", meta = (AllowPrivateAccess = "true"))
	int cur_SkillCount;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "NORMAL ATTACK", meta = (AllowPrivateAccess = "true"))
	int max_SkillCount;

/// Gimic Properties
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "GIMIC", meta = (AllowPrivateAccess = "true"))
	int GimicTotalCount = 3;

	// Fst Gimic - Spawn Monster by Hp Rate
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SPAWN", meta = (AllowPrivateAccess = "true"))
	float SpawnHpPercent;
	UPROPERTY(VisibleAnywhere, Category = "SPAWN", meta = (AllowPrivateAccess = "true"))
	float beforeHpRate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SPAWN", meta = (AllowPrivateAccess = "true"))
	TArray<ADownGradeMonsterSpawner*> SpawnerFstArray;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SPAWN", meta = (AllowPrivateAccess = "true"))
	TArray<ADownGradeMonsterSpawner*> SpawnerSndArray;

	// Hp Percent Event Properties
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "HP GIMIC", meta = (AllowPrivateAccess = "true"))
	float FstHpGimicRate;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "HP GIMIC", meta = (AllowPrivateAccess = "true"))
	float SndHpGimicRate;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "HP GIMIC", meta = (AllowPrivateAccess = "true"))
	float HpGimicDuration;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "HP GIMIC", meta = (AllowPrivateAccess = "true"))
	float HpGimicSlowRate;
	bool bIsHpGimicFstStart;
	bool bIsHpGimicSndStart;
	
public:
///Getter
	// Default 
	int GetBossPase() const { return CurrentPase; }
	int GetCenterByDistance() const { return DistanceToCenter; }
	AActor* GetCenterArrow() const { return CenterArrow; }
	float GetRotateSpeed() const { return fRotateSpeed; }

	bool GetEscapse() const { return IsEscape; }
	bool GetOrbitING() const { return bIsOrbitING; }

	// Normal Attack
	int GetNormalAtkType() const { return NormalAttackTotalCount; }

	// Gimic
	int GetGimicType() const { return GimicTotalCount; }

///Setter
	UFUNCTION(BlueprintCallable)
	void SetEscape(const bool newBool) { IsEscape = newBool; }
	UFUNCTION(BlueprintCallable)
	void SetOrbitING(const bool newBool) { bIsOrbitING = newBool; }
	UFUNCTION(BlueprintCallable)
	void SetRotateSpeed(const float newFloat) { fRotateSpeed = newFloat; }
};
