// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEliteMonster.h"
#include "Components/CapsuleComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"

ABaseEliteMonster::ABaseEliteMonster()
{
	PrimaryActorTick.bCanEverTick = true;

	SpecificEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Specific Effect"));
	SpecificEffect->SetupAttachment(GetCapsuleComponent());
}

void ABaseEliteMonster::BeginPlay()
{
	Super::BeginPlay();

	//변수 초기화
	currentAtkCount = 0;

	SpecificEffect->Deactivate();
}

void ABaseEliteMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

int ABaseEliteMonster::MeleeAttack_Implementation()
{
	if (isBigAttack)	//강한 공격을 사용하는 경우 처리
	{
		BigAttackFunc();	//BP에서 정의

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

void ABaseEliteMonster::AttachMoreWeapon(TSubclassOf<AMonster_Weapon> Weapon, FName socketName)
{
	WeaponInstance2 = GetWorld()->SpawnActor<AMonster_Weapon>(Weapon, GetMesh()->GetSocketTransform(socketName, ERelativeTransformSpace::RTS_World));
	WeaponInstance2->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, socketName);
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

