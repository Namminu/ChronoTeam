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

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void OpenOtherBossPortal(int paseNum);
	
	UFUNCTION(BlueprintImplementableEvent)
	void Boss2PaseAttachPin();
	UFUNCTION(BlueprintImplementableEvent)
	void Boss3PaseAttachPin();

	UFUNCTION(BlueprintCallable)
	void TempAttachPin(TSubclassOf<AChrono_JustMeshPin> Weapon, FName WeaponSocket);

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
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void CalculateStrikeHitRange();


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
	void StrikeGimic(int GimicNum);

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

	// Default Properties
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "DEFAULT", meta = (AllowPrivateAccess = "true"))
	float DistanceToCenter;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "DEFAULT", meta = (AllowPrivateAccess = "true"))
	bool bIsAttack;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "DEFAULT", meta = (AllowPrivateAccess = "true"))
	bool bIsGimic;

	bool IsEscape;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "MOVE", meta = (AllowPrivateAccess = "true"))
	bool bIsOrbitFinish;

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
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "GIMIC", meta = (AllowPrivateAccess = "true"))
	int GimicTotalCount;

	// Fst Gimic - Spawn Monster by Hp Rate
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SPAWN", meta = (AllowPrivateAccess = "true"))
	float SpawnHpPercent;
	UPROPERTY(VisibleAnywhere, Category = "SPAWN", meta = (AllowPrivateAccess = "true"))
	float beforeHpRate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SPAWN", meta = (AllowPrivateAccess = "true"))
	TArray<ADownGradeMonsterSpawner*> SpawnerFstArray;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SPAWN", meta = (AllowPrivateAccess = "true"))
	TArray<ADownGradeMonsterSpawner*> SpawnerSndArray;

public:
///Getter
	// Default 
	int GetBossPase() const { return CurrentPase; }
	int GetCenterByDistance() const { return DistanceToCenter; }
	AActor* GetCenterArrow() const { return CenterArrow; }

	bool GetEscapse() const { return IsEscape; }
	bool GetOrbitFinish() const { return bIsOrbitFinish; }

	// Normal Attack
	int GetNormalAtkType() const { return NormalAttackTotalCount; }

	// Gimic
	int GetGimicType() const { return GimicTotalCount; }

///Setter
	UFUNCTION(BlueprintCallable)
	void SetEscape(const bool newBool) { IsEscape = newBool; }
	UFUNCTION(BlueprintCallable)
	void SetOrbitFinish(const bool newBool) { bIsOrbitFinish = newBool; }
};
