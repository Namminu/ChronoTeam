// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseElite_MagicianMonster.h"
#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"
#include <Blueprint/AIBlueprintHelperLibrary.h>
#include "AI_Controller_.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "MonsterSpawner.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include <Kismet/GameplayStatics.h>
#include "GameFramework/CharacterMovementComponent.h"
#include "Monster_Weapon.h"

ABaseElite_MagicianMonster::ABaseElite_MagicianMonster()
{
	PrimaryActorTick.bCanEverTick = true;

	//BigAttackRangeBox = CreateDefaultSubobject<USphereComponent>(TEXT("Big Attack Range"));
	//BigAttackRangeBox->SetupAttachment(GetCapsuleComponent());

	DiePortalEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Die Portal"));
	DiePortalEffect->SetupAttachment(GetCapsuleComponent());

}

void ABaseElite_MagicianMonster::BeginPlay()
{
	Super::BeginPlay();

	SetFlashMTI();		//Set Flash MTI after Change MTI <- Opaque

	//Cast to Player
	player = Cast<ATeamChronoCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	if (player == nullptr) UE_LOG(LogTemp, Error, TEXT("Magicball has Cast failed to Player"));

	//isBigAck = false;
	isMontage = false;
	isCanAttack = false;

	DiePortalEffect->Deactivate();

	SetisFstGimic(false);
	SetisSndGimic(false);

	AssginToArray();
	SetTimerFunc();

	//Set BlackBoard Property to true So Can Take Damage Immediately
	UAIBlueprintHelperLibrary::GetAIController(GetOwner())->GetBlackboardComponent()->SetValueAsBool("CanTakeDamage", true);
}

void ABaseElite_MagicianMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (isCanAttack)
	{
		CheckDistancePlayer();
	}
}

/// <summary>
/// 일반 공격 범위 Overlap
/// </summary>
void ABaseElite_MagicianMonster::OnRangeOverlapBegin(UPrimitiveComponent* const OverlappedComponent,
	AActor* const otherActor, UPrimitiveComponent* const OtherComponent,
	int const OtherBodyIndex, bool const FromSweep, FHitResult const& SweepResult)
{
	if (otherActor == this) return;

	if (otherActor->ActorHasTag("PLAYER"))
	{
		isCanAttack = true;
		UAIBlueprintHelperLibrary::GetAIController(this)->GetBlackboardComponent()->SetValueAsBool("PlayerIsInAttackRange", true);
	}

}

void ABaseElite_MagicianMonster::OnRangeOverlapEnd(UPrimitiveComponent* const OverlappedComponent,
	AActor* const otherActor, UPrimitiveComponent* const OtherComponent, int const OtherBodyIndex)
{
	if (otherActor == this) return;

	if (otherActor->ActorHasTag("PLAYER"))
	{
		//isBigAck = true;
		//UAIBlueprintHelperLibrary::GetAIController(this)->GetBlackboardComponent()->SetValueAsBool("isPlayerNormalRange", false);

		isCanAttack = false;
		UAIBlueprintHelperLibrary::GetAIController(this)->GetBlackboardComponent()->SetValueAsBool("PlayerIsInAttackRange", false);
	}

}

int ABaseElite_MagicianMonster::MeleeAttack_Implementation()
{
	Super::MeleeAttack_Implementation();

	return 0;
}

/// <summary>
/// ReDefine mon_Death in Magician
/// </summary>
void ABaseElite_MagicianMonster::mon_Death_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("Magician Death Func Called"));

	//Stop all Montages Before Death
	GetMesh()->GetAnimInstance()->StopAllMontages(NULL);

	//GetBigAttackRange()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//WhyOnlyUGetDown();

	//Stop Movement
	GetCharacterMovement()->SetMovementMode(MOVE_None);
	//Stop Collision
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetAttackRangeColl()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//GetWeaponColl()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	AAI_Controller_* monsterAI = Cast<AAI_Controller_>(GetController());
	monsterAI->StopAI();	//Stop BT 
	DetachFromControllerPendingDestroy();
	
	//Pause Death Montage On Layback
	DeathFunc();
}

void ABaseElite_MagicianMonster::InitFunc_Implementation()
{
	Super::InitFunc_Implementation();
}

void ABaseElite_MagicianMonster::mon_Destroy()
{
	Destroy();
	GetWeaponInstance_Fst()->Destroy();
}

void ABaseElite_MagicianMonster::RealDestroy()
{
	Destroy();
	GetWeaponInstance_Fst()->Wp_Destroy();

	UE_LOG(LogTemp, Warning, TEXT("Call Destroy Func by MagicianMonster"));
}

void ABaseElite_MagicianMonster::SetTimerFunc()
{
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ABaseElite_MagicianMonster::SpawnMonster, SpawnDelay, true);
}

void ABaseElite_MagicianMonster::MakeBigAttack_Implementation()
{
}

void ABaseElite_MagicianMonster::SpawnMonster()
{
	for (ADownGradeMonsterSpawner* Spawner : SpawnerArray)
	{
		if (Spawner)
		{
			//Spawn Monster
			Spawner->MonsterSpawn();
		}
	}
}

float ABaseElite_MagicianMonster::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	//Check is Playing Make Barrier Animation
	if (!isMontage)
	{
		//Not Invincible = Damage Apply to Monster directly
		if (!GetInvincible())
		{
			//Check Monster Born for not Take Damage in Born_Animation
			if (GetIsBorn())
			{
				SetMonCurrentHp(GetMonCurrentHp() - DamageAmount);
				//if Monster Hp under Zero, Get Die
				if (GetMonCurrentHp() <= 0)
				{
					SetMonsterLive(false);
					//UAIBlueprintHelperLibrary::GetAIController(this)->GetBlackboardComponent()->SetValueAsBool("IsMonsterLive", false);
					mon_Death();					//Magician Die
					return 0.f;
				}
				DamageFlash();

				//if Monster Hp under Gimic Hp, Start Gimic
				if (GetMonCurrentHp() <= GetMonMaxHp() * (Get_FstGimicHp() / 100) && !GetisFstGimic())
				{
					UE_LOG(LogTemp, Error, TEXT("First Gimic Start"));
					SetisFstGimic(true);			//Change Property to Not Take FstGimic Again
					SetInvincible(true);			//Not for Take Damage

					//Set BlackBoard Properties to Make Barrier
					UAIBlueprintHelperLibrary::GetAIController(this)->GetBlackboardComponent()->SetValueAsBool("CanTakeDamage", false);
					UAIBlueprintHelperLibrary::GetAIController(this)->GetBlackboardComponent()->SetValueAsBool("IsMontageEnd", false);
				}

				if (GetMonCurrentHp() <= GetMonMaxHp() * (Get_SndGimicHp() / 100) && !GetisSndGimic())
				{
					UE_LOG(LogTemp, Error, TEXT("Second Gimic Start"));
					//
					SetisSndGimic(true);			//Change Property to Not Take SndGimic Again
					SetInvincible(true);			//Not for Take Damage

					//Set BlackBoard Properties to Make Barrier
					UAIBlueprintHelperLibrary::GetAIController(this)->GetBlackboardComponent()->SetValueAsBool("CanTakeDamage", false);
					UAIBlueprintHelperLibrary::GetAIController(this)->GetBlackboardComponent()->SetValueAsBool("IsMontageEnd", false);				
				}
			}
		}
		//Invincible = Damage Apply to Barrier
		else
		{
			//Take Damage only by Magic_Ball
			if (DamageCauser && DamageCauser->ActorHasTag("MAGICBALL"))
			{
				SetBarrierHp(GetBarrierHp() - DamageAmount);
				//if Barrier Hp under Zero, Set Invincible false for Take Damage for Monster
				if (GetBarrierHp() <= 0)
				{
					SetInvincible(false);
					GetSpecificEffect()->Deactivate();
					UE_LOG(LogTemp, Error, TEXT("Gimic End"));
					return 0.f;
				}
				BarrierFlash();
			}
		}
	}

	return 0.0f;
}