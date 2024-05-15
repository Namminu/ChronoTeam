// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base_Boss.h"
#include "Chrono_JustMeshPin.h"
#include "Boss_Chrono_ShadowPartner.generated.h"

/**
 * 
 */
UCLASS()
class TEAMCHRONO_API ABoss_Chrono_ShadowPartner : public ABase_Boss
{
	GENERATED_BODY()

public:
	ABoss_Chrono_ShadowPartner();

protected:
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called when Actor Destroy
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
/// Attack Funcs
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void Shapa_LaunchPins();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void Shapa_DashAttack();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void Shapa_LaserAttack();

/// Override Funcs
	int MeleeAttack_Implementation() override;

	void Boss_Death_Implementation() override;

	void AttackFunc_Implementation(int caseNum) override;

/// Local Funcs
	UFUNCTION(BlueprintCallable)
	void SetupCenterArrow(class AActor* centerArrow);

	UFUNCTION(BlueprintCallable)
	void TempAttachPin(TSubclassOf<AChrono_JustMeshPin> Weapon, FName WeaponSocket);

	UFUNCTION(BlueprintCallable)
	int GetRandomAttackNum(int min, int max);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void LoopByChronoPase(int ChronoPase);

	UFUNCTION(BlueprintCallable)
	void SetMTI();

	UFUNCTION(BlueprintCallable)
	void SetPinMeshMTI();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void ChangeOpacity(int start, int end);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void ClockPinChangeOpacity(int start, int end);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void StayLookPlayer(FVector TargetLocation, float newTime);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void CheckDisappearTime();

/// Timer Funcs	
	UFUNCTION()
	void Shapa_AttackEnd();

	UFUNCTION(BlueprintCallable)
	void SetAttackTimer();
	UFUNCTION(BlueprintCallable)
	void ResetAttackTimer();
	UFUNCTION(BlueprintCallable)
	void CallAttackBB();

private:
/// Counting Properties
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ATTACK", meta = (AllowPrivateAccess = "true"))
	int LifeAttackCount;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ATTACK", meta = (AllowPrivateAccess = "true"))
	int CurrentAttackCount;

/// Center Arrow
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default", meta = (AllowPrivateAccess = "true"))
	class AActor* CenterArrow;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "MOVE", meta = (AllowPrivateAccess = "true"))
	bool shapa_OrbitING;

/// SKM
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SKM", meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* sk_Halo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Collision, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* coll_Box;

/// Weapon
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	TArray<AChrono_JustMeshPin*> ClockPinArray;

/// MTI
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MTI", meta = (AllowPrivateAccess = "true"))
	class UMaterialInstanceDynamic* MTI;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MTI", meta = (AllowPrivateAccess = "true"))
	TArray<UMaterialInstanceDynamic*> ClockPinMTIArray;

/// Attack Timer
	FTimerHandle ShapaAttackTimer;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ATTACK", meta = (AllowPrivateAccess = "true"))
	float ShapaAttackDelay;

public:
/// Getter
	AActor* GetCenterArrow() const { return CenterArrow; }
	bool GetShapaOrbitING() const { return shapa_OrbitING; }

/// Setter
	UFUNCTION(BlueprintCallable)
	void SetShapaOrbitING(const bool newBool) { shapa_OrbitING = newBool; }
};
