// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base_Boss.h"
#include <Fighter_Fst_Marble.h>
#include "Boss_Fighter.generated.h"

/**
 * 
 */

UCLASS()
class TEAMCHRONO_API ABoss_Fighter : public ABase_Boss
{
	GENERATED_BODY()
	
public:
	ABoss_Fighter();

protected:
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called when Actor Destroy
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;


public:
// Fighter Local Funcs
	void SetupFMTI(class USkeletalMeshComponent* skeleton, int index);

	void SetFullFMTI();

// Override Funcs
	int MeleeAttack_Implementation() override;

	void Boss_Death_Implementation() override;

	/// <summary>
	/// Fighter Normal Attack Func
	/// 0 : Default Normal Attack
	/// 1 : Snd Normal Attack - every Twice
	/// 2 : Trd Normal Attack - every Triple
	/// </summary>
	/// <param name="caseNum"></param>
	void AttackFunc_Implementation(int caseNum) override;

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void SetJumpAttackLocation();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void BeforeJumpRotate();

	float TakeDamage(float DamageAmount,
		struct FDamageEvent const& DamageEvent,
		AController* EventInstigator,
		AActor* DamageCauser) override;

	void DamageFlash_Implementation() override;

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
	void Calculate_DefaultAttack();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void Calculate_SndAttack();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void Calculate_TrdAttack();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void Calculate_JumpAttack();

// Gimic Funcs
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void FstGimic();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void Fst_SpawnEffect();
	UFUNCTION(BlueprintCallable)
	void Fst_MarbleChange();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Fst_SpawnArrow();


	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void SndGimic();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void TrdGimic();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void FothGimic();

private:
/// Skeletal Mesh
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SKM", meta =(AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* sk_Helm;	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SKM", meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* sk_Shoulders;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SKM", meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* sk_Chest;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SKM", meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* sk_Belt;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SKM", meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* sk_Legs;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SKM", meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* sk_Cape;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SKM", meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* sk_Hands;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SKM", meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* sk_Bracers;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SKM", meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* sk_Boots;

/// Flash MTI Init Array
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DAMAGE FLASH", meta = (AllowPrivateAccess = "true"))
	TArray<FLinearColor> InitColors;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DAMAGE FLASH", meta = (AllowPrivateAccess = "true"))
	float InitMutiplier;

/// Gimic Properties
	// Normal Attack Count Properties
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "NORMAL ATTACK", meta = (AllowPrivateAccess = "true"))
	int Current_SndCount;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "NORMAL ATTACK", meta = (AllowPrivateAccess = "true"))
	int Snd_AttackCount;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "NORMAL ATTACK", meta = (AllowPrivateAccess = "true"))
	int Current_TrdCount;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "NORMAL ATTACK", meta = (AllowPrivateAccess = "true"))
	int Trd_AttackCount;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "JUMP ATTACK", meta = (AllowPrivateAccess = "true"))
	float JumpDistance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "JUMP ATTACK", meta = (AllowPrivateAccess = "true"))
	bool isJump;

	//콤보 공격인지 체크
	bool isComboNow;
	//몇번째 공격중인지 체크
	bool isSndComboNow;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "FST GIMIC", meta = (AllowPrivateAccess = "true"))
	int Fst_CurrentAttackCount;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "FST GIMIC", meta = (AllowPrivateAccess = "true"))
	int Fst_MaxAttackCount;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "FST GIMIC", meta = (AllowPrivateAccess = "true"))
	TArray<AFighter_Fst_Marble*> Fst_MarbleArray;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "FST GIMIC", meta = (AllowPrivateAccess = "true"))
	int Fst_MaxMarbleCount;

public:
///Getter
	bool GetComboCheck() const { return isComboNow; }
	bool GetComboNumCheck() const { return isSndComboNow; }
	UFUNCTION(BlueprintCallable)
	TArray<AFighter_Fst_Marble*> GetMarbleArray() const { return Fst_MarbleArray; }
	int GetFstAttackCount() const { return Fst_CurrentAttackCount; }
	int GetFstMaxCount() const { return Fst_MaxAttackCount; }
	int GetFstMaxMarbleCount() const { return Fst_MaxMarbleCount; }

///Setter
	void SetComboCheck(const bool newBool) { isComboNow = newBool; }
	void SetComboNum(const bool newBool) { isSndComboNow = newBool; }

	void SetFstAttackCount(const int newCount) { Fst_CurrentAttackCount = newCount; }
	UFUNCTION(BlueprintImplementableEvent)
	void ClearMarbleArray();
};
