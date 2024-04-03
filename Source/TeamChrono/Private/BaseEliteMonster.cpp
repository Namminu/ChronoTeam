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

	//���� �ʱ�ȭ
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
	if (isBigAttack)	//���� ������ ����ϴ� ��� ó��
	{
		BigAttackFunc();	//BP���� ����
	}
	else	//���� ������ ������� �ʴ� ��� ó��
	{
		PlayAnimMontage(GetAtkMontage());	//�Ϲ� ����
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
	if (otherActor == this) return;		//��Ʈ�ڽ��� �ڱ� �ڽſ��� ����� ��� �ƹ� ����x

	if (otherActor->ActorHasTag("PLAYER"))	//��Ʈ�ڽ��� �÷��̾�� ����� ��� = �÷��̾� ���� ��
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

			else if (isInvincible)	//���� ���� = ����� �ϴ� ���� = ���� ü���� �̶� ���� �� �ֵ��� ��
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
	//ù��° ��� ���� + �ι�° ��� ����x
	if (isFstGimic&&!isSndGimic)
	{
		BarrierHp = Fst_BarrierHp;
	}
	//ù��° ��� Ȯ�� + �ι�° ��� ���� O
	else if (isFstGimic&&isSndGimic)
	{
		BarrierHp = Snd_BarrierHp;
	}
	SetGimicTimer();
}