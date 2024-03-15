// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEliteMonster.h"
#include "Components/CapsuleComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include <Kismet/GameplayStatics.h>
#include <Blueprint/AIBlueprintHelperLibrary.h>
#include "AI_Controller_.h"
#include "BehaviorTree/BlackboardComponent.h"

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
	isInvincible = false;

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
	}
	else	//강한 공격을 사용하지 않는 경우 처리
	{
		PlayAnimMontage(GetAtkMontage());	//일반 공격
	}
	return 0;
}

void ABaseEliteMonster::EliteGimic_Implementation()
{
	UAIBlueprintHelperLibrary::GetAIController(this)->GetBlackboardComponent()->SetValueAsBool("IsGimic", true);
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
	if (otherActor == this) return;		//히트박스가 자기 자신에게 닿았을 경우 아무 영향x

	if (otherActor->ActorHasTag("PLAYER"))	//히트박스가 플레이어에게 닿았을 경우 = 플레이어 공격 시
	{
		UE_LOG(LogTemp, Warning, TEXT("Monster hit Player"));

		UGameplayStatics::ApplyDamage(otherActor, GetMonAtk(), nullptr, this, GetDamageType());
	}
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
		UAIBlueprintHelperLibrary::GetAIController(this)->GetBlackboardComponent()->SetValueAsBool("PlayerIsInMeleeRange", true);
	}
}

void ABaseEliteMonster::OnRangeOverlapEnd(UPrimitiveComponent* const OverlappedComponent,
	AActor* const otherActor, UPrimitiveComponent* const OtherComponent, 
	int const OtherBodyIndex)
{
	if (otherActor == this) return;

	if (otherActor->ActorHasTag("PLAYER"))
	{
		UAIBlueprintHelperLibrary::GetAIController(this)->GetBlackboardComponent()->SetValueAsBool("PlayerIsInMeleeRange", false);
	}
}

float ABaseEliteMonster::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (!isInvincible)
	{
		Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

		//기믹 시작 Hp인지 확인
		//근데 조건을 == 으로 하면 오버데미지의 경우 호출이 안되는데? 어떻게 고치지
		if (GetMonCurrentHp() == call_FstGimicHp || GetMonCurrentHp() == call_SndGimicHp)
		{
			EliteGimic();
		}

		return DamageAmount;
	}
	else return 0.f;
}

