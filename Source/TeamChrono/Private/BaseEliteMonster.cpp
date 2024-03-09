// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEliteMonster.h"

ABaseEliteMonster::ABaseEliteMonster()
{
	PrimaryActorTick.bCanEverTick = true;


}

void ABaseEliteMonster::BeginPlay()
{
	Super::BeginPlay();

	//변수 초기화
	currentAtkCount = 0;
}

void ABaseEliteMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

int ABaseEliteMonster::MeleeAttack_Implementation()
{
	if (isBigAttack)	//강한 공격을 사용하는 경우 처리
	{
		BigAttackFunc();

		//currentAtkCount++;
		//if (currentAtkCount < 3)
		//{
		//	PlayAnimMontage(GetAtkMontage());	//일반 공격
		//}
		//else if (currentAtkCount >= 3)
		//{
		//	PlayAnimMontage(BigAtkMontage);	//강한 공격
		//	currentAtkCount = 0;	//공격 횟수 초기화
		//}
	}
	else	//강한 공격을 사용하지 않는 경우 처리
	{
		PlayAnimMontage(GetAtkMontage());	//일반 공격
	}
	return 0;
}

