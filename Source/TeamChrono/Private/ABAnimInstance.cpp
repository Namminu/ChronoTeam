// Fill out your copyright notice in the Description page of Project Settings.


#include "ABAnimInstance.h"

UABAnimInstance::UABAnimInstance()
{
	static ConstructorHelpers::FObjectFinder <UAnimMontage> ATTACK_MONTAGE
	(TEXT("/Game/PlayerCharacter/Animation/Montage/AM_AttackMontage.AM_AttackMontage"));

	if (ATTACK_MONTAGE.Succeeded())
		AttackMontage = ATTACK_MONTAGE.Object;
}

void UABAnimInstance::PlayAttackMontage()
{
	Montage_Play(AttackMontage, 1.0f);
}

void UABAnimInstance::JumpToAttackMontageSection(int32 NewSection)
{
	Montage_JumpToSection(GetAttackMontageSectionName(NewSection), AttackMontage);
	NextAttacking = false;
}

void UABAnimInstance::AnimNotify_AttackHitCheck()
{
	//Broadcast = 델리게이트 안에 있는 모든 함수 실행
	OnAttackHitCheck.Broadcast();
}

void UABAnimInstance::AnimNotify_NextAttackCheck()
{

	NextAttackCheck();
}

void UABAnimInstance::NextAttackCheck()
{
	//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("NextAttackCheck")));
	OnNextAttackCheck.Broadcast();
}


FName UABAnimInstance::GetAttackMontageSectionName(int32 Section)
{

	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("Attack%d"), Section));
	return FName(*FString::Printf(TEXT("Attack%d"), Section));
}