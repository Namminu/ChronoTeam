// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEliteMonster.h"
#include "Components/CapsuleComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include <Kismet/GameplayStatics.h>
#include <Blueprint/AIBlueprintHelperLibrary.h>
#include "AI_Controller_.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Monster_Weapon.h"

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
	isInvincible = true;
	isPowerUpPlaying = false;

	isFstGimic = false;
	isSndGimic = false;

	isMTI = false;

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

void ABaseEliteMonster::PlayGimicMontage()
{
	PlayAnimMontage(GetGimicMontage());
}

void ABaseEliteMonster::SetGimicTimer_Implementation()
{
}

void ABaseEliteMonster::ReSetTimer_Implementation()
{
}

void ABaseEliteMonster::OnAttackOverlapBegin(UPrimitiveComponent* const OverlappedComponent,
	AActor* const otherActor, UPrimitiveComponent* const OtherComponent, 
	int const OtherBodyIndex, bool const FromSweep, 
	FHitResult const& SweepResult)
{
	if (otherActor == this) return;		//히트박스가 자기 자신에게 닿았을 경우 아무 영향x

	if (otherActor->ActorHasTag("PLAYER"))	//히트박스가 플레이어에게 닿았을 경우 = 플레이어 공격 시
	{
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
	//Take Damage After Born AnimMontage
	if (GetIsBorn())
	{
		//Take Damage After Gimic AnimMontage
		if (!isPowerUpPlaying)
		{
			if (!isInvincible)
			{
				Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

				//Check Monster Hp for First Gimic Time
				if (GetMonCurrentHp() <= GetMonMaxHp() * (call_FstGimicHp / 100) && !isFstGimic)
				{
					isFstGimic = true;
					UAIBlueprintHelperLibrary::GetAIController(this)->GetBlackboardComponent()->SetValueAsBool("CanTakeDamage", false);
					EliteGimic();
				}
				//Check Monster Hp for  Gimic Time
				if (GetMonCurrentHp() <= GetMonMaxHp() * (call_SndGimicHp / 100) && !isSndGimic)
				{
					isSndGimic = true;
					UAIBlueprintHelperLibrary::GetAIController(this)->GetBlackboardComponent()->SetValueAsBool("CanTakeDamage", false);
					EliteGimic();
				}
				return DamageAmount;
			}

			else if (isInvincible)	//무적 상태 = 기믹을 하는 상태 = 방어막의 체력이 이때 까일 수 있도록 함
			{
				DamageWeaponFlash();
				BarrierHp -= DamageAmount;
				if (BarrierHp <= 0)
				{
					UAIBlueprintHelperLibrary::GetAIController(this)->GetBlackboardComponent()->SetValueAsBool("IsGimicClear", true);
				}
			}
		}		
	}
	return 0.f;
}

void ABaseEliteMonster::ReNewBarrierHp()
{
	//첫번째 기믹 시작 + 두번째 기믹 시작x
	if (isFstGimic&&!isSndGimic)
	{
		BarrierHp = Fst_BarrierHp;
	}
	//첫번째 기믹 확인 + 두번째 기믹 시작 O
	else if (isFstGimic&&isSndGimic)
	{
		BarrierHp = Snd_BarrierHp;
	}
	SetGimicTimer();
}