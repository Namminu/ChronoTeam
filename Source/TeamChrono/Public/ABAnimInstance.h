// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "ABAnimInstance.generated.h"


//�������� ���� �� �ִ� ��������Ʈ ����
DECLARE_MULTICAST_DELEGATE(FOnNextAttackCheckDelegate);
DECLARE_MULTICAST_DELEGATE(FOnAttackHitCheckDelegate);

/**
 *
 */
UCLASS()
class TEAMCHRONO_API UABAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UABAnimInstance();
	void PlayAttackMontage();
	void JumpToAttackMontageSection(int32 NewSection);

	FOnNextAttackCheckDelegate OnNextAttackCheck;
	FOnAttackHitCheckDelegate  OnAttackHitCheck;

	UFUNCTION(BlueprintCallable)
	void NextAttackCheck();


private:

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	UAnimMontage* AttackMontage;

	UFUNCTION()
	void AnimNotify_AttackHitCheck();
	UFUNCTION()
	void AnimNotify_NextAttackCheck();



	FName GetAttackMontageSectionName(int32 Section);

};