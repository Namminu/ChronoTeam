// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEliteMonster.h"

ABaseEliteMonster::ABaseEliteMonster()
{
	PrimaryActorTick.bCanEverTick = true;


}

void ABaseEliteMonster::BeginPlay()
{
	Super::BeginPlay();

	//���� �ʱ�ȭ
	currentAtkCount = 0;
}

void ABaseEliteMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

int ABaseEliteMonster::MeleeAttack_Implementation()
{
	if (isBigAttack)	//���� ������ ����ϴ� ��� ó��
	{
		BigAttackFunc();

		//currentAtkCount++;
		//if (currentAtkCount < 3)
		//{
		//	PlayAnimMontage(GetAtkMontage());	//�Ϲ� ����
		//}
		//else if (currentAtkCount >= 3)
		//{
		//	PlayAnimMontage(BigAtkMontage);	//���� ����
		//	currentAtkCount = 0;	//���� Ƚ�� �ʱ�ȭ
		//}
	}
	else	//���� ������ ������� �ʴ� ��� ó��
	{
		PlayAnimMontage(GetAtkMontage());	//�Ϲ� ����
	}
	return 0;
}

