// Fill out your copyright notice in the Description page of Project Settings.


#include "Boss_TimeMaster.h"
#include <Blueprint/AIBlueprintHelperLibrary.h>
#include "BossAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Chrono_Weapon_ClockPin.h"
#include "Chrono_JustMeshPin.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "GI_Chrono.h"


ABoss_TimeMaster::ABoss_TimeMaster()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	sk_Halo = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Halo"));
	sk_Halo->SetupAttachment(GetMesh());
	sk_Halo->SetLeaderPoseComponent(GetMesh());

	ArrowCollBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Coll for Arrow"));
	ArrowCollBox->SetupAttachment(GetCapsuleComponent());
}

void ABoss_TimeMaster::BeginPlay()
{
	IsEscape = false;
	bIsOrbitING = false;

	Super::BeginPlay();

	// Reset Boss To Can Fight
	SetIsCanFight(true);
	UAIBlueprintHelperLibrary::GetAIController(this)->GetBlackboardComponent()->SetValueAsBool("IsCanFight", true);
	// Reset Flash Material For Damage Flash
	SetFlashMT(GetMesh(), 0);
	// Setup Halo Material Instance
	HaloMTI = sk_Halo->CreateDynamicMaterialInstance(0);
	// Reset Every Attack Count Properties
	cur_StrikeCount = 0;
	cur_SkillCount = 0;
	// Check Boss State Properties by Custom Game Instance
	CheckStateFunc();
}

void ABoss_TimeMaster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABoss_TimeMaster::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void ABoss_TimeMaster::CheckStateFunc()
{
	//Check is Chrono 2Pase
	if (((GetMyGI()->GetChronoNowHp() / GetMyGI()->GetChronoMaxHp()) * 100) >= f_3PaseHp &&
		((GetMyGI()->GetChronoNowHp() / GetMyGI()->GetChronoMaxHp()) * 100) <= f_2PaseHp)
	{
		// About Pase Properties
		CurrentPase = 2;
		is2PaseStart = true;
		is3PaseStart = false;
		// About Hp Gimic Properties
		bIsHpGimicFstStart = false;
		bIsHpGimicSndStart = false;
		// About Boss Hp Percent Properties
		SetBossMaxHp(GetMyGI()->GetChronoMaxHp());
		SetBossCurrentHp(GetMyGI()->GetChronoNowHp());
		UpdateHpPercent();
		// Attach Clock Pins for 2Pase
		Boss2PaseAttachPin();
		// About Boss Hp for Spawn Monster Properties
		beforeHpRate = GetMyGI()->GetChrono_SpawnHpRate();
		// About Change Halo Color
		ChangeHaloColor(Pase2Color);
		// About Is Enable Player Skill
		GetPlayerProperty()->SetIsCanESkill(true);
		GetPlayerProperty()->SetIsCanQSkill(false);
		GetPlayerProperty()->SetIsCanTabSkill(false);
		SetPlayerSKillUI(2);
	}
	//Check is Chrono 3Pase
	else if (((GetMyGI()->GetChronoNowHp() / GetMyGI()->GetChronoMaxHp()) * 100) <= f_3PaseHp &&
		((GetMyGI()->GetChronoNowHp() / GetMyGI()->GetChronoMaxHp()) * 100) <= f_2PaseHp)
	{
		// About Pase Properties
		CurrentPase = 3;
		is2PaseStart = true;
		is3PaseStart = true;
		// About Hp Gimic Properties
		bIsHpGimicFstStart = true;
		bIsHpGimicSndStart = false;
		// About Boss Hp Percent Properties
		SetBossMaxHp(GetMyGI()->GetChronoMaxHp());
		SetBossCurrentHp(GetMyGI()->GetChronoNowHp());
		UpdateHpPercent();
		// Attach Clock Pins for 3Pase
		Boss2PaseAttachPin();
		Boss3PaseAttachPin();
		// About Boss Hp for Spawn Monster Properties
		beforeHpRate = GetMyGI()->GetChrono_SpawnHpRate();
		// About Change Halo Color
		ChangeHaloColor(Pase3Color);
		// About Is Enable Player Skill
		GetPlayerProperty()->SetIsCanESkill(true);
		GetPlayerProperty()->SetIsCanQSkill(true);
		GetPlayerProperty()->SetIsCanTabSkill(false);
		SetPlayerSKillUI(3);
	}
	//Check is Chrono 1Pase
	else
	{
		// About Pase Properties
		CurrentPase = 1;
		is2PaseStart = false;
		is3PaseStart = false;
		// About Hp Gimic Properties
		bIsHpGimicFstStart = false;
		bIsHpGimicSndStart = false;
		// About Boss Hp Percent Properties
		SetBossMaxHp(GetMyGI()->GetChronoMaxHp());
		SetBossCurrentHp(GetMyGI()->GetChronoNowHp());
		UpdateHpPercent();
		// About Boss Hp for Spawn Monster Properties
		beforeHpRate = GetMyGI()->GetChrono_SpawnHpRate();
		// About Is Enable Player Skill
		GetPlayerProperty()->SetIsCanESkill(false);
		GetPlayerProperty()->SetIsCanQSkill(false);
		GetPlayerProperty()->SetIsCanTabSkill(false);
		SetPlayerSKillUI(1);
	}
}

int ABoss_TimeMaster::GetRandomAttackNum(int min, int max)
{
	int num = FMath::RandRange(min, max);
	if (BeforeAttackNum == num && num == 1)
	{
		return GetRandomAttackNum(min, max);
	}
	else
	{
		BeforeAttackNum = num;
		return num;
	}
}

void ABoss_TimeMaster::SetFlashMT(USkeletalMeshComponent* skeleton, int index)
{
	FlashMT = skeleton->CreateDynamicMaterialInstance(index);
	FlashMT->GetVectorParameterValue(TEXT("EmissiveColor"), InitColor);
	FlashMT->GetScalarParameterValue(TEXT("EmissiveMutiplier"), InitMultiplier);
}

void ABoss_TimeMaster::CheckCurrentPase()
{
	if (!(GetBossCurrentHp() <= 0))
	{
		// Set Pase 2
		if ((GetBossCurrentHp() / GetBossMaxHp()) * 100 <= f_2PaseHp && (GetBossCurrentHp() / GetBossMaxHp()) * 100 > f_3PaseHp)
		{
			if (!is2PaseStart)
			{
				is2PaseStart = true;
				CurrentPase = 2;
				SetInvincible(true);
				UAIBlueprintHelperLibrary::GetAIController(this)->GetBlackboardComponent()->SetValueAsBool("ChangeSetup", true);
				UAIBlueprintHelperLibrary::GetAIController(this)->GetBlackboardComponent()->SetValueAsBool("IsPaseChange", true);

				ResetAttackTimer();
			}
		}
		// Set Pase 3
		else if (((GetBossCurrentHp() / GetBossMaxHp()) * 100 <= f_3PaseHp) && is2PaseStart)
		{
			if (!is3PaseStart)
			{
				is3PaseStart = true;
				CurrentPase = 3;
				SetInvincible(true);
				UAIBlueprintHelperLibrary::GetAIController(this)->GetBlackboardComponent()->SetValueAsBool("ChangeSetup", true);
				UAIBlueprintHelperLibrary::GetAIController(this)->GetBlackboardComponent()->SetValueAsBool("IsPaseChange", true);

				ResetAttackTimer();
			}
		}
	}	
}

void ABoss_TimeMaster::CheckSpawnHpRate()
{
	// Check Hp Percent When Boss Doesn't Die
	if (!(GetBossCurrentHp() <= 0))
	{
		float currentHpRate = ((GetBossCurrentHp() / GetBossMaxHp()) * 100);

		if ((beforeHpRate - currentHpRate) >= SpawnHpPercent)
		{
			beforeHpRate = beforeHpRate - SpawnHpPercent;			
			SpawnMonsterFlip();
			// Update Spawn Hp Rate into Custom Game Instance
			GetMyGI()->SetChrono_SpawnHpRate(beforeHpRate);
		}
	}
}

void ABoss_TimeMaster::CheckOpenTimeDelayZone()
{
	if ((GetBossCurrentHp() / GetBossMaxHp()) * 100 <= FstHpGimicRate && !bIsHpGimicFstStart)
	{
		bIsHpGimicFstStart = true;
		SetInvincible(true);
		UAIBlueprintHelperLibrary::GetAIController(this)->GetBlackboardComponent()->SetValueAsBool("ChangeSetup", true);
		UAIBlueprintHelperLibrary::GetAIController(this)->GetBlackboardComponent()->SetValueAsBool("IsPaseChange", false);
		ResetAttackTimer();
	}

	else if ((GetBossCurrentHp() / GetBossMaxHp()) * 100 <= SndHpGimicRate && !bIsHpGimicSndStart)
	{
		bIsHpGimicSndStart = true;
		SetInvincible(true);
		UAIBlueprintHelperLibrary::GetAIController(this)->GetBlackboardComponent()->SetValueAsBool("ChangeSetup", true);
		UAIBlueprintHelperLibrary::GetAIController(this)->GetBlackboardComponent()->SetValueAsBool("IsPaseChange", false);
		ResetAttackTimer();
	}
}

void ABoss_TimeMaster::TempAttachPin(TSubclassOf<AChrono_JustMeshPin> Weapon, FName WeaponSocket)
{
	class AChrono_JustMeshPin* ClockPin;
	ClockPin = GetWorld()->SpawnActor<AChrono_JustMeshPin>(Weapon, GetMesh()->GetSocketTransform(WeaponSocket, ERelativeTransformSpace::RTS_World));
	ClockPin->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, WeaponSocket);
	ClockPinArray.AddUnique(ClockPin);
}

void ABoss_TimeMaster::ChangeMoveOrbitDirection()
{
	float RandomPC = FMath::FRand() * 100;
	if (RandomPC < NormalPC) fRotateSpeed = 1.f;
	else fRotateSpeed = -1.f;
}

void ABoss_TimeMaster::DestroyAllChrono()
{
	for (AChrono_JustMeshPin* PinMesh : ClockPinArray)
	{
		if (PinMesh)
		{
			PinMesh->Destroy();
		}
	
	}
	for (AChrono_Weapon_ClockPin* ClockWeapon : ClockPinWeapon)
	{
		if (ClockWeapon)
		{
			ClockWeapon->Destroy();
		}	
	}

	Super::InitFunc_Implementation(GetActorLocation());

	Destroy();
}

void ABoss_TimeMaster::ResetSpawner()
{
	for (ADownGradeMonsterSpawner* SpawnerFst : SpawnerFstArray)
	{
		SpawnerFst->InitFunc();
	}
	for (ADownGradeMonsterSpawner* SpawnerSnd : SpawnerSndArray)
	{
		SpawnerSnd->InitFunc();
	}
}

void ABoss_TimeMaster::SpawnerInSequence()
{
	for (ADownGradeMonsterSpawner* SpawnerFst : SpawnerFstArray)
	{
		SpawnerFst->ResetInSequence();
	}
	for (ADownGradeMonsterSpawner* SpawnerSnd : SpawnerSndArray)
	{
		SpawnerSnd->ResetInSequence();
	}
}

int ABoss_TimeMaster::MeleeAttack_Implementation()
{
	ResetAttackTimer();
	// Default Normal Attack / Not Strike, Not Gimic
	if (cur_StrikeCount < max_StrikeCount && cur_SkillCount < max_SkillCount)
	{
		AttackFunc(GetRandomAttackNum(0, NormalAttackTotalCount - 1));
		cur_StrikeCount++;
		cur_SkillCount++;
	}
	// Strike Attack / Not Normal Attack, Not Gimic
	else if (cur_StrikeCount >= max_StrikeCount && cur_SkillCount < max_SkillCount)
	{
		AttackFunc(3);
		cur_StrikeCount = 0;
	}
	// Gimic Attack / Not Normal Attack, Not Strike Attack 
	else if (cur_StrikeCount < max_StrikeCount && cur_SkillCount >= max_SkillCount)
	{
		GimicFunc(GetRandomAttackNum(1, GimicTotalCount));
		cur_SkillCount = 0;
	}
	else
	{
		StrikeGimic();
		cur_StrikeCount = 0;
		cur_SkillCount = 0;
	}
	ChangeMoveOrbitDirection();

	return 0;
}

void ABoss_TimeMaster::Boss_Death_Implementation()
{
	Super::Boss_Death_Implementation();
	//ClearMyBoss();
	StartChronoEndSequence();
}

void ABoss_TimeMaster::InitFunc_Implementation(FVector FirstLocation)
{
	//Reset Boss Properties by Game Instance
	GetMyGI()->SetChronoNowHp(GetMyGI()->GetChronoMaxHp());
	GetMyGI()->SetChrono_SpawnHpRate(100);

	ResetSpawner();
}

void ABoss_TimeMaster::AttackFunc_Implementation(int caseNum)
{
}

float ABoss_TimeMaster::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (!GetInvincible())
	{
		Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
		DamageFlash();
		//Save Current Chrono Hp into myGI
		GetMyGI()->SetChronoNowHp(GetBossCurrentHp());
	}
	//Check Boss Pase for Damage Change & Load Other Boss Stage
	CheckCurrentPase();
	//Check Boss Hp Percent for Spawn Normal Monsters
	CheckSpawnHpRate();
	//Check Boss Hp Percent for Start Player Slow Scene
	CheckOpenTimeDelayZone();

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

void ABoss_TimeMaster::AttackEnd()
{
	UAIBlueprintHelperLibrary::GetAIController(this)->GetBlackboardComponent()->SetValueAsBool("IsAttack", false);
	SetAttackTimer();
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
