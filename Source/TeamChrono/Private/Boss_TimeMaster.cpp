// Fill out your copyright notice in the Description page of Project Settings.


#include "Boss_TimeMaster.h"
#include <Blueprint/AIBlueprintHelperLibrary.h>
#include "BossAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

ABoss_TimeMaster::ABoss_TimeMaster()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	sk_Halo = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Halo"));
	sk_Halo->SetupAttachment(GetMesh());
	sk_Halo->SetLeaderPoseComponent(GetMesh());
}

void ABoss_TimeMaster::BeginPlay()
{
	IsEscape = false;

	Super::BeginPlay();

	// Reset Flash Material For Damage Flash
	SetFlashMT(GetMesh(), 0);
	// Reset Every Attack Count Properties
	cur_StrikeCount = 0;
	cur_SkillCount = 0;
	// Reset Checking Attack Type Properties
	bIsAttack = false;
	bIsGimic = false;
	// Reset Boss Pase Properties
	CurrentPase = 1;
	is2PaseStart = false;
	is3PaseStart = false;
	// Reset Boss Damage
	BossDamage = 1;
}

void ABoss_TimeMaster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//if (!bIsAttack&&!bIsGimic)
	//{
	//	SetFarfromPlayer(DistanceToPlayer);
	//}
}

void ABoss_TimeMaster::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

int ABoss_TimeMaster::GetRandomAttackNum(int min, int max)
{
	return FMath::RandRange(min, max);
}

void ABoss_TimeMaster::SetFlashMT(USkeletalMeshComponent* skeleton, int index)
{
	FlashMT = skeleton->CreateDynamicMaterialInstance(index);
	FlashMT->GetVectorParameterValue(TEXT("EmissiveColor"), InitColor);
	FlashMT->GetScalarParameterValue(TEXT("EmissiveMutiplier"), InitMultiplier);
}

void ABoss_TimeMaster::CheckCurrentPase()
{
	if ((GetBossCurrentHp() / GetBossMaxHp()) <= f_2PaseHp && (GetBossCurrentHp() / GetBossMaxHp()) > f_3PaseHp)
	{
		CurrentPase = 2;
		if (!is2PaseStart)
		{
			is2PaseStart = true;
			UAIBlueprintHelperLibrary::GetAIController(this)->GetBlackboardComponent()->SetValueAsBool("ChangePase", true);
			//OpenOtherBossPortal(CurrentPase);
		}
	}
	else if ((GetBossCurrentHp() / GetBossMaxHp()) <= f_3PaseHp)
	{
		CurrentPase = 3;
		if (!is3PaseStart)
		{
			is3PaseStart = true;
			UAIBlueprintHelperLibrary::GetAIController(this)->GetBlackboardComponent()->SetValueAsBool("ChangePase", true);
			//OpenOtherBossPortal(CurrentPase);
		}
	}
}

void ABoss_TimeMaster::AttachWeaponPin(TSubclassOf<AChrono_Weapon_ClockPin> Weapon, FName WeaponSocket)
{

}

int ABoss_TimeMaster::MeleeAttack_Implementation()
{
	// Default Normal Attack / Not Strike, Not Gimic
	if (cur_StrikeCount < max_StrikeCount && cur_SkillCount < max_SkillCount)
	{
		bIsAttack = true;

		AttackFunc(GetRandomAttackNum(0, NormalAttackTotalCount));
		cur_StrikeCount++;
		cur_SkillCount++;
	}
	// Strike Attack / Not Normal Attack, Not Gimic
	else if (cur_StrikeCount >= max_StrikeCount && cur_SkillCount < max_SkillCount)
	{
		bIsAttack = true;

		AttackFunc(3);
	 	cur_StrikeCount = 0;
	}
	// Gimic Attack / Not Normal Attack, Not Strike Attack 
	else if (cur_StrikeCount < max_StrikeCount && cur_SkillCount >= max_SkillCount)
	{
		bIsGimic = true;

		GimicFunc(GetRandomAttackNum(0, GimicTotalCount));
		cur_SkillCount = 0;
	}
	// Both Gimic Attack and Strike Attack / Not Normal Attack
	else if (cur_StrikeCount >= max_SkillCount && cur_SkillCount >= max_SkillCount)
	{
		bIsAttack = true;
		bIsGimic = true;

		StrikeGimic(GetRandomAttackNum(0, GimicTotalCount));
		cur_StrikeCount = 0;
		cur_SkillCount = 0;
	}

	return 0;
}

void ABoss_TimeMaster::Boss_Death_Implementation()
{
	Super::Boss_Death_Implementation();
}

//void ABoss_TimeMaster::InitFunc_Implementation()
//{
//	Super::InitFunc_Implementation();
//
//}

void ABoss_TimeMaster::AttackFunc_Implementation(int caseNum)
{
}

float ABoss_TimeMaster::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (!GetInvincible())
	{
		Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
		DamageFlash();
	}
	//Check Boss Pase for Damage Change & Load Other Boss Stage
	CheckCurrentPase();

	return 0.0f;
}

void ABoss_TimeMaster::DamageFlash_Implementation()
{
}

void ABoss_TimeMaster::OnRangeOverlapBegin(UPrimitiveComponent* const OverlappedComponent,
	AActor* const otherActor, UPrimitiveComponent* const OtherComponent, 
	int const OtherBodyIndex, bool const FromSweep, FHitResult const& SweepResult)
{
}

void ABoss_TimeMaster::OnRangeOverlapEnd(UPrimitiveComponent* const OverlappedComponent,
	AActor* const otherActor, UPrimitiveComponent* const OtherComponent, int const OtherBodyIndex)
{
}

void ABoss_TimeMaster::SetAttackTimer()
{
	GetWorld()->GetTimerManager().SetTimer(AttackTimer, this, &ABoss_TimeMaster::CallAttackBB, AttackDelay, true);
}

void ABoss_TimeMaster::ResetAttackTimer()
{
	GetWorld()->GetTimerManager().ClearTimer(AttackTimer);
}

void ABoss_TimeMaster::CallAttackBB()
{
	UAIBlueprintHelperLibrary::GetAIController(this)->GetBlackboardComponent()->SetValueAsBool("IsAttack", true);
}
