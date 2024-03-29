// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseMonster.h"
#include "BaseEliteMonster.generated.h"

/**
 * 
 */
UCLASS()
class TEAMCHRONO_API ABaseEliteMonster : public ABaseMonster
{
	GENERATED_BODY()
	
public:
	ABaseEliteMonster();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	int MeleeAttack_Implementation() override;

	//강한 공격 관련 정의 - in BP
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void BigAttackFunc();

	//엘리트 몬스터 기믹 관련 정의 - in BP
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void EliteGimic();

	UFUNCTION(BlueprintCallable)
	void AttachMoreWeapon(TSubclassOf<AMonster_Weapon> Weapon, FName socketName);

	UFUNCTION(BlueprintCallable)
	void PlayGimicMontage();

	//기믹 전 사전 동작 함수
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void beforeGimic();

	//기믹 - 베리어 체력 갱신 용 타이머 함수
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SetGimicTimer();

	//기믹 - 베리어 타이머 해제 함수
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ReSetTimer();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void ChangeMTI();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void DamageWeaponFlash();

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
/// 
	UFUNCTION(BlueprintCallable)
	void ReNewBarrierHp();

private:
/// 강한 공격 부분 변수
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ELITE ATTACK", meta = (AllowPrivateAccess = "true"))
	bool isBigAttack;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ELITE ATTACK", meta = (AllowPrivateAccess = "true"))
	int BigAttackCount;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ELITE ATTACK", meta = (AllowPrivateAccess = "true"))
	int currentAtkCount;

///
	//강한 공격 애니메이션 몽타주
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation, meta = (AllowPrivateAccess = "true"))
	UAnimMontage* BigAtkMontage_Fst;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation, meta = (AllowPrivateAccess = "true"))
	UAnimMontage* BigAtkMontage_Snd;

	//기믹용 애니메이션 몽타주
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GIMIC ANIMATION", meta = (AllowPrivateAccess = "true"))
	UAnimMontage* Gimic_Montage;
///
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WEAPON", meta = (AllowPrivateAccess = "true"))
	AMonster_Weapon* WeaponInstance2;

///
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "EFFECT", meta = (AllowPrivateAccess = "true"))
	class UNiagaraComponent* SpecificEffect;

///
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ELITE ATTACK", meta = (AllowPrivateAccess = "true"))
	float call_FstGimicHp;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ELITE ATTACK", meta = (AllowPrivateAccess = "true"))
	float call_SndGimicHp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ELITE ATTACK", meta = (AllowPrivateAccess = "true"))
	bool isInvincible;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ELITE ATTACK", meta = (AllowPrivateAccess = "true"))
	float BarrierHp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ELITE ATTACK", meta = (AllowPrivateAccess = "true"))
	float Fst_BarrierHp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ELITE ATTACK", meta = (AllowPrivateAccess = "true"))
	float Snd_BarrierHp;

	bool isFstGimic;
	bool isSndGimic;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool isMTI;

///Setter
public:
	void SetInvincible(bool newBollSet) { isInvincible = newBollSet; }
	void SetBarrierHp(const float newHp) { BarrierHp = newHp; }

	void SetisFstGimic(const bool newBool) { isFstGimic = newBool; }
	void SetisSndGimic(const bool newBool) { isSndGimic = newBool; }

///Getter
	UAnimMontage* GetGimicMontage() { return Gimic_Montage; }
	UNiagaraComponent* GetSpecificEffect() { return SpecificEffect; }

	UFUNCTION(BlueprintCallable)
	float GetBarrierHp() { return BarrierHp; }

	bool GetInvincible() const { return isInvincible; }

	float Get_FstGimicHp() const { return call_FstGimicHp; }
	float Get_SndGimicHp() const { return call_SndGimicHp; }

	bool GetisFstGimic() const { return isFstGimic; }
	bool GetisSndGimic() const { return isSndGimic; }

};
