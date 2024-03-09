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

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void BigAttackFunc();

private:
/// 강한 공격 부분 변수
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ELITE ATTACK", meta = (AllowPrivateAccess = "true"))
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
};
