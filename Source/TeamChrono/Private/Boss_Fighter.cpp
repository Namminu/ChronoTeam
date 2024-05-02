// Fill out your copyright notice in the Description page of Project Settings.


#include "Boss_Fighter.h"
#include <Blueprint/AIBlueprintHelperLibrary.h>
#include "BossAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Base_BossWeapon.h"

ABoss_Fighter::ABoss_Fighter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set Parts SuitUp
	sk_Helm = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Helmet Mesh"));
	sk_Helm->SetupAttachment(GetMesh());
	sk_Helm->SetLeaderPoseComponent(GetMesh());

	sk_Shoulders = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Shoulders Mesh"));
	sk_Shoulders->SetupAttachment(GetMesh());
	sk_Shoulders->SetLeaderPoseComponent(GetMesh());

	sk_Chest = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Chest Mesh"));
	sk_Chest->SetupAttachment(GetMesh());
	sk_Chest->SetLeaderPoseComponent(GetMesh());

	sk_Belt = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Belt Mesh"));
	sk_Belt->SetupAttachment(GetMesh());
	sk_Belt->SetLeaderPoseComponent(GetMesh());

	sk_Legs = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Legs Mesh"));
	sk_Legs->SetupAttachment(GetMesh());
	sk_Legs->SetLeaderPoseComponent(GetMesh());

	sk_Cape = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Cape Mesh"));
	sk_Cape->SetupAttachment(GetMesh());
	sk_Cape->SetLeaderPoseComponent(GetMesh());

	sk_Hands = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Hands Mesh"));
	sk_Hands->SetupAttachment(GetMesh());
	sk_Hands->SetLeaderPoseComponent(GetMesh());

	sk_Bracers = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Bracers Mesh"));
	sk_Bracers->SetupAttachment(GetMesh());
	sk_Bracers->SetLeaderPoseComponent(GetMesh());

	sk_Boots = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Boots Mesh"));
	sk_Boots->SetupAttachment(GetMesh());
	sk_Boots->SetLeaderPoseComponent(GetMesh());
	
}

void ABoss_Fighter::BeginPlay()
{
	Super::BeginPlay();

	// Reset Bool Properties for Check Gimic Ready
	isFstGimic = false;
	isSndGimic = false;
	isTrdGimic = false;
	isFothGimic = false;

	// Setup All Flash MTI
	SetFullFMTI();

	//Reset Attack Count Properties
	Current_SndCount = 0;
	Current_TrdCount = 0;

	isComboNow = false;
	isSndComboNow = false;

	//Reset Fst Gimic Properties
	Fst_CurrentAttackCount = 0;

	//Reset Snd GImic Properties
	isJumpMontageING = false;

	//Reset Trd GImic Properties
	TrdGimicCurrentCount = 0;
	TrdGimicCurrentLightning = 0;

	//Reset Foth Gimic Properties
	FothGimicHpPercent = 20.f;
	FothGimic_1stStarted = false;
	FothGimic_2ndStarted = false;
	FothGimic_3rdStarted = false;
	FothGimic_4thStarted = false;
	FotheGimic_MontageING = false;
	FothGimic_MontageEnd = false;
}

void ABoss_Fighter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Player is So Far From Boss So Jump Attack To player
	if (GetIsCanFight())
	{
		if (!isJump)
		{
			if (GetDistanceTo(GetPlayerProperty()) >= JumpDistance)
			{
				UAIBlueprintHelperLibrary::GetAIController(this)->GetBlackboardComponent()->SetValueAsBool("IsPlayerSoFar", true);
			}
			else
			{
				UAIBlueprintHelperLibrary::GetAIController(this)->GetBlackboardComponent()->SetValueAsBool("IsPlayerSoFar", false);
			}
		}
	}
}

void ABoss_Fighter::DamageFlash_Implementation()
{
	GetBossWeapon()->DamageFlash();
	//Boss Body Flash Code Written in BP
}

//void ABoss_Fighter::InitFunc_Implementation()
//{
//	Super::InitFunc_Implementation();
//
//	// Reset Bool Properties for Check Gimic Ready
//	isFstGimic = false;
//	isSndGimic = false;
//	isTrdGimic = false;
//	isFothGimic = false;
//
//	//Reset Attack Count Properties
//	Current_SndCount = 0;
//	Current_TrdCount = 0;
//
//	isComboNow = false;
//	isSndComboNow = false;
//
//	//Reset Fst Gimic Properties
//	Fst_CurrentAttackCount = 0;
//
//	//Reset Snd GImic Properties
//	isJumpMontageING = false;
//
//	//Reset Trd GImic Properties
//	TrdGimicCurrentCount = 0;
//	TrdGimicCurrentLightning = 0;
//
//	//Reset Foth Gimic Properties
//	FothGimicHpPercent = 20.f;
//	FothGimic_1stStarted = false;
//	FothGimic_2ndStarted = false;
//	FothGimic_3rdStarted = false;
//	FothGimic_4thStarted = false;
//	FotheGimic_MontageING = false;
//	FothGimic_MontageEnd = false;
//
//	ClearTornadoArray();
//	ClearMarbleArray();
//}

int ABoss_Fighter::MeleeAttack_Implementation()
{
	if (!isJump)
	{
		Super::MeleeAttack_Implementation();
	}

	//2번째 공격, 3번째 공격 둘 다 아닐 때
	if (Current_SndCount < Snd_AttackCount && Current_TrdCount < Trd_AttackCount)
	{
		AttackFunc(0);
		Current_SndCount++;
		Current_TrdCount++;
		//For Fst Gimic Attack
		Fst_CurrentAttackCount++;
		//For Trd Gimic Attack
		CheckTrdAttackCount();
	}
	//2번째 공격이고 3번째 공격 아닐 때
	else if (Current_SndCount >= Snd_AttackCount && Current_TrdCount < Trd_AttackCount)
	{
		AttackFunc(1);
		Current_SndCount = 0;
		//For Fst Gimic Attack
		Fst_CurrentAttackCount++;
		//For Trd Gimic Attack
		CheckTrdAttackCount();
	}
	//2번째 공격 아니고 3번째 공격일 때
	else if (Current_SndCount < Snd_AttackCount && Current_TrdCount >= Trd_AttackCount)
	{
		AttackFunc(3);
		Current_TrdCount = 0;
		//For Fst Gimic Attack
		Fst_CurrentAttackCount++;
		//For Trd Gimic Attack
		CheckTrdAttackCount();
	}
	//2번째 공격이고 3번째 공격일 때 (두 개가 겹칠 때)
	else if(Current_SndCount >= Snd_AttackCount && Current_TrdCount >= Trd_AttackCount)
	{
		isComboNow = true;
		AttackFunc(0);
		Current_SndCount = 0;
		Current_TrdCount = 0;
		//For Fst Gimic Attack
		Fst_CurrentAttackCount++;
		//For Trd Gimic Attack
		CheckTrdAttackCount();
	}

	return 0;
}

void ABoss_Fighter::Boss_Death_Implementation()
{
	GetBossWeapon()->Destroy();
	AttachWeapon(GetBossWeapon()->GetClass(), "Weapon_ReverseSocket");

	Super::Boss_Death_Implementation();
}

void ABoss_Fighter::AttackFunc_Implementation(int caseNum)
{
}

float ABoss_Fighter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (!GetInvincible())
	{
		Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
		DamageFlash();

		// Check Hp for Foth Gimic Start
	}
	CheckHpPercent();

	return 0.0f;
}

void ABoss_Fighter::OnRangeOverlapBegin(UPrimitiveComponent* const OverlappedComponent, 
	AActor* const otherActor, UPrimitiveComponent* const OtherComponent, 
	int const OtherBodyIndex, bool const FromSweep, FHitResult const& SweepResult)
{
	if (otherActor == this) return;

	if (otherActor->ActorHasTag("PLAYER"))
	{
		UAIBlueprintHelperLibrary::GetAIController(this)->GetBlackboardComponent()->SetValueAsBool("PlayerIsInMeleeRange", true);
	}
}

void ABoss_Fighter::OnRangeOverlapEnd(UPrimitiveComponent* const OverlappedComponent,
	AActor* const otherActor, UPrimitiveComponent* const OtherComponent, int const OtherBodyIndex)
{
	if (otherActor == this) return;

	if (otherActor->ActorHasTag("PLAYER"))
	{
		UAIBlueprintHelperLibrary::GetAIController(this)->GetBlackboardComponent()->SetValueAsBool("PlayerIsInMeleeRange", false);
	}
}

void ABoss_Fighter::SetupFMTI(class USkeletalMeshComponent* skeleton, int index)
{
	UMaterialInstanceDynamic* MT = skeleton->CreateDynamicMaterialInstance(index);
	FLinearColor ColorValue;
	MT->GetVectorParameterValue(TEXT("EmissiveColor"), ColorValue);
	SetFlashMTIArray_Implementation(MT);
	InitColors.Add(ColorValue);
}

void ABoss_Fighter::SetFullFMTI()
{
	//Mesh
	SetupFMTI(GetMesh(), 0);
	SetupFMTI(GetMesh(), 1);
	SetupFMTI(GetMesh(), 2);
	//Boots
	SetupFMTI(sk_Boots, 0);
	SetupFMTI(sk_Boots, 1);
	//Bracers
	SetupFMTI(sk_Bracers, 0);
	//Hands
	SetupFMTI(sk_Hands, 0);
	//Cape
	SetupFMTI(sk_Cape, 0);
	SetupFMTI(sk_Cape, 1);
	//Legs
	SetupFMTI(sk_Legs, 0);
	//Belt
	SetupFMTI(sk_Belt, 0);
	//Shoulders
	SetupFMTI(sk_Shoulders, 0);
	//Chest
	SetupFMTI(sk_Chest, 0);
	SetupFMTI(sk_Chest, 1);
	//Helm
	SetupFMTI(sk_Helm, 0);
}

void ABoss_Fighter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

}

void ABoss_Fighter::FstGimic_Implementation()
{
	if (!isSndGimic && !isTrdGimic && !isFothGimic)
	{
		isFstGimic = true;
		//Set Gimic On
		UAIBlueprintHelperLibrary::GetAIController(this)->GetBlackboardComponent()->SetValueAsBool("IsGimic", true);
		UAIBlueprintHelperLibrary::GetAIController(this)->GetBlackboardComponent()->SetValueAsBool("IsTimerGimic", false);
		UAIBlueprintHelperLibrary::GetAIController(this)->GetBlackboardComponent()->SetValueAsBool("IsFstGimic", true);
		// Pause Snd Gimic Timer
		SetPauseSndTimer();
	}
}

void ABoss_Fighter::Fst_MarbleChange()
{
	for (AFighter_Fst_Marble* Marble : Fst_MarbleArray)
	{
		if (Marble)
		{
			Marble->SetEffectToBarrier();
		}
	}

	FTimerHandle TimerHandle;
	float delay = 1.3f;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ABoss_Fighter::Fst_SpawnArrow, delay, false);
}

void ABoss_Fighter::SndGimic_Implementation()
{
	if (!isFstGimic && !isTrdGimic && !isFothGimic)
	{
		//Check Snd Gimic Start
		isSndGimic = true;

		//Set Snd Gimic On
		UAIBlueprintHelperLibrary::GetAIController(this)->GetBlackboardComponent()->SetValueAsBool("IsGimic", true);
		UAIBlueprintHelperLibrary::GetAIController(this)->GetBlackboardComponent()->SetValueAsBool("IsTimerGimic", true);
		UAIBlueprintHelperLibrary::GetAIController(this)->GetBlackboardComponent()->SetValueAsBool("IsSndGimic", true);
		// Set Off Gimic Timer
		SetClearSndTimer();
	}
}

void ABoss_Fighter::SetSndGimicTimer()
{
	GetWorld()->GetTimerManager().SetTimer(SndGimicTimerHandle, this, &ABoss_Fighter::SndGimic_Implementation, Snd_GimicDelay, true);
}

void ABoss_Fighter::Fst_SpawnArrow_Implementation()
{
	UE_LOG(LogTemp, Error, TEXT("Spawn Arrow Func Called"));
}

void ABoss_Fighter::SetPauseSndTimer()
{
	GetWorld()->GetTimerManager().PauseTimer(SndGimicTimerHandle);
}

void ABoss_Fighter::SetResumeSndTimer()
{
	GetWorld()->GetTimerManager().UnPauseTimer(SndGimicTimerHandle);
}

void ABoss_Fighter::SetClearSndTimer()
{
	GetWorld()->GetTimerManager().ClearTimer(SndGimicTimerHandle);
}

void ABoss_Fighter::TrdGimic_Implementation()
{
	if (!isFstGimic && !isSndGimic && !isFothGimic)
	{
		isTrdGimic = true;
		UAIBlueprintHelperLibrary::GetAIController(this)->GetBlackboardComponent()->SetValueAsBool("IsGimic", true);
		UAIBlueprintHelperLibrary::GetAIController(this)->GetBlackboardComponent()->SetValueAsBool("IsTimerGimic", false);
		UAIBlueprintHelperLibrary::GetAIController(this)->GetBlackboardComponent()->SetValueAsBool("IsTrdGimic", true);
	}
}

void ABoss_Fighter::CheckTrdAttackCount()
{
	TrdGimicCurrentCount++;
	if (TrdGimicCurrentCount >= TrdGimicAttackMaxCount)
	{
		TrdGimic_Implementation();
		TrdGimicCurrentCount = 0;
	}
}

void ABoss_Fighter::FothGimic_Implementation()
{
	isFothGimic = true;
	UAIBlueprintHelperLibrary::GetAIController(this)->GetBlackboardComponent()->SetValueAsBool("IsGimic", true);
	UAIBlueprintHelperLibrary::GetAIController(this)->GetBlackboardComponent()->SetValueAsBool("IsTimerGimic", false);
	UAIBlueprintHelperLibrary::GetAIController(this)->GetBlackboardComponent()->SetValueAsBool("IsFothGimic", true);
}

void ABoss_Fighter::CheckHpPercent()
{
	int CurrentPercent = ((GetBossCurrentHp() / GetBossMaxHp()) * 100);

	if (CurrentPercent <= 80 && CurrentPercent > 60 && !FothGimic_1stStarted)
	{
		if (!isFstGimic && !isSndGimic && !isTrdGimic)
		{
			SetInvincible(true);
			FothGimic_1stStarted = true;
			FothGimic_Implementation();

			UE_LOG(LogTemp, Error, TEXT("Foth Gimic 1 Start"));
		}
	}
	else if (CurrentPercent <= 60 && CurrentPercent > 40 && !FothGimic_2ndStarted)
	{
		if (!isFstGimic && !isSndGimic && !isTrdGimic)
		{
			SetInvincible(true);
			FothGimic_2ndStarted = true;
			FothGimic_Implementation();

			UE_LOG(LogTemp, Error, TEXT("Foth Gimic 2 Start"));
		}
	}
	else if (CurrentPercent <= 40 && CurrentPercent > 20 && !FothGimic_3rdStarted)
	{
		if (!isFstGimic && !isSndGimic && !isTrdGimic)
		{
			SetInvincible(true);
			FothGimic_3rdStarted = true;
			FothGimic_Implementation();

			UE_LOG(LogTemp, Error, TEXT("Foth Gimic 3 Start"));
		}
	}
	else if (CurrentPercent <= 20 && CurrentPercent > 0 && !FothGimic_4thStarted)
	{
		if (!isFstGimic && !isSndGimic && !isTrdGimic)
		{
			SetInvincible(true);
			FothGimic_4thStarted = true;
			FothGimic_Implementation();

			UE_LOG(LogTemp, Error, TEXT("Foth Gimic 4 Start"));
		}
	}
}

/*
	if (!isFstGimic && !isSndGimic && !isTrdGimic)
	{
*/