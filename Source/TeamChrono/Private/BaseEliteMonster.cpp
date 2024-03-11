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
		BigAttackFunc();	//BP���� ����

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

void ABaseEliteMonster::OnAttackOverlapBegin(UPrimitiveComponent* const OverlappedComponent, 
	AActor* const otherActor, UPrimitiveComponent* const OtherComponent, 
	int const OtherBodyIndex, bool const FromSweep, 
	FHitResult const& SweepResult)
{

}

void ABaseEliteMonster::OnAttackOverlapEnd(UPrimitiveComponent* const OverlappedComponent,
	AActor* const otherActor, UPrimitiveComponent* const OtherComponent, 
	int const OtherBodyIndex)
{

}

void ABaseEliteMonster::OnRangeOverlapBegin(UPrimitiveComponent* const OverlappedComponent,
	AActor* const otherActor, UPrimitiveComponent* const OtherComponent, 
	int const OtherBodyIndex, bool const FromSweep, 
	FHitResult const& SweepResult)
{
	if (otherActor == this) return;

	if (otherActor->ActorHasTag("PLAYER"))
	{
		UE_LOG(LogTemp, Error, TEXT("Elite Monster Can Attack Player Now"));
	}
}

void ABaseEliteMonster::OnRangeOverlapEnd(UPrimitiveComponent* const OverlappedComponent,
	AActor* const otherActor, UPrimitiveComponent* const OtherComponent, 
	int const OtherBodyIndex)
{
	if (otherActor == this) return;

	if (otherActor->ActorHasTag("PLAYER"))
	{
		UE_LOG(LogTemp, Error, TEXT("Elite Monster Can Not Attack Player Now"));
	}
}

