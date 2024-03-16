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

	//���� ���� ���� ���� - in BP
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void BigAttackFunc();

	//����Ʈ ���� ��� ���� ���� - in BP
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void EliteGimic();

	UFUNCTION(BlueprintCallable)
	void AttachMoreWeapon(TSubclassOf<AMonster_Weapon> Weapon, FName socketName);

	UFUNCTION(BlueprintCallable)
	void PlayGimicMontage();

	//��� �� ���� ���� �Լ�
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void beforeGimic();

/// Overlap Event Function 
	void OnAttackOverlapBegin(UPrimitiveComponent* const OverlappedComponent,
		AActor* const otherActor,
		UPrimitiveComponent* const OtherComponent,
		int const OtherBodyIndex,
		bool const FromSweep,
		FHitResult const& SweepResult);

	void OnAttackOverlapEnd(UPrimitiveComponent* const OverlappedComponent,
		AActor* const otherActor,
		UPrimitiveComponent* const OtherComponent,
		int const OtherBodyIndex);

	void OnRangeOverlapBegin(UPrimitiveComponent* const OverlappedComponent,
		AActor* const otherActor,
		UPrimitiveComponent* const OtherComponent,
		int const OtherBodyIndex,
		bool const FromSweep,
		FHitResult const& SweepResult);

	void OnRangeOverlapEnd(UPrimitiveComponent* const OverlappedComponent,
		AActor* const otherActor,
		UPrimitiveComponent* const OtherComponent,
		int const OtherBodyIndex);

	float TakeDamage(float DamageAmount,
		struct FDamageEvent const& DamageEvent,
		AController* EventInstigator,
		AActor* DamageCauser) override;
/// 


private:
/// ���� ���� �κ� ����
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ELITE ATTACK", meta = (AllowPrivateAccess = "true"))
	bool isBigAttack;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ELITE ATTACK", meta = (AllowPrivateAccess = "true"))
	int BigAttackCount;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ELITE ATTACK", meta = (AllowPrivateAccess = "true"))
	int currentAtkCount;

///
	//���� ���� �ִϸ��̼� ��Ÿ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation, meta = (AllowPrivateAccess = "true"))
	UAnimMontage* BigAtkMontage_Fst;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation, meta = (AllowPrivateAccess = "true"))
	UAnimMontage* BigAtkMontage_Snd;

	//��Ϳ� �ִϸ��̼� ��Ÿ��
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

	UPROPERTY()
	bool isInvincible;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ELITE ATTACK", meta = (AllowPrivateAccess = "true"))
	float BarrierHp;

///Setter
public:
	void SetInvincible(bool newBollSet) { isInvincible = newBollSet; }

///Getter
	UAnimMontage* GetGimicMontage() { return Gimic_Montage; }
};
