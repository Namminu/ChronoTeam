// Fill out your copyright notice in the Description page of Project Settings.


#include "Boss_Golem.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include <Kismet/GameplayStatics.h>
#include <Blueprint/AIBlueprintHelperLibrary.h>
#include "BossAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

ABoss_Golem::ABoss_Golem()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Setup Parts Break Effect
	L_PartsBreakEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Left Break Effect"));
	L_PartsBreakEffect->SetupAttachment(GetMesh());
	R_PartsBreakEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Right Break Effect"));
	R_PartsBreakEffect->SetupAttachment(GetMesh());
}

void ABoss_Golem::BeginPlay()
{
	Super::BeginPlay();

	//Set Gimic Bool Properties
	CurrentAtkCount = 0;
	isTrdGimicCanAttack = false;
	isTrdGimicNow = false;

	isFst_GimicStart = false;

	isFoth01_GimicStart = false;
	isFoth02_GimicStart = false;

	//Create Dynamic Material Instance for Damage Flash
	SetFstMTI(GetMesh()->CreateDynamicMaterialInstance(0));
	SetFlashMTIArray_Implementation(GetFstMTI());

	//Set off Niagara Effect
	L_PartsBreakEffect->Deactivate();
	R_PartsBreakEffect->Deactivate();

	//Set Timer Gimic - Snd Gimic : Jump and player Grab
	SetSndGimicTimer();
}					   

void ABoss_Golem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Check When Not Jumping
	if (!isJump&&!isTrdGimicNow)
	{
		//Player is So Far From Golem So Jump Attack To player
		if (GetDistanceTo(GetPlayerProperty()) >= distanceToPlayer)
		{
			UAIBlueprintHelperLibrary::GetAIController(this)->GetBlackboardComponent()->SetValueAsBool("IsPlayerSoFar", true);
		}
		else
		{
			UAIBlueprintHelperLibrary::GetAIController(this)->GetBlackboardComponent()->SetValueAsBool("IsPlayerSoFar", false);
		}
	}

}

int ABoss_Golem::MeleeAttack_Implementation()
{
	if (!isJump)
	{
		Super::MeleeAttack_Implementation();
	}

	//Call Normal Attack Func
	if (CurrentAtkCount < MaxAtkCount)
	{
		AttackFunc(0);
		CurrentAtkCount++;
	}
	else
	{
		isTrdGimicNow = true;
		TrdGimic();
	}

	return 0;
}

void ABoss_Golem::Boss_Death_Implementation()
{
	Super::Boss_Death_Implementation();

	/*FTimerHandle TimerHandle;
	float delay = 4.3f;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ABoss_Golem::Golem_Destroy, delay, false);*/
}

float ABoss_Golem::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent,
	AController* EventInstigator, AActor* DamageCauser)
{
	//Can Take Damage When Boss Not Invincible
	if (!GetInvincible())
	{
		Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

		DamageFlash();

		//Fst_Gimic Start
		if (GetBossCurrentHp() <= GetBossMaxHp() * (FstGimic_StartHp / 100) && !isFst_GimicStart)
		{
			isFst_GimicStart = true;
			isFst_GimicIng = true;
			//
			SetInvincible(true);

			UE_LOG(LogTemp, Warning, TEXT("Golem First Gimic Start"));
			FstGimic();

			//Pause Snd Gimic Timer
			GetWorld()->GetTimerManager().ClearTimer(SndGimicTimerHandle);
		}
		//Fouth_Gimic_01 Start
		if (GetBossCurrentHp() <= GetBossMaxHp() * (FothGimic_01_StartHp / 100) && !isFoth01_GimicStart)
		{
			isFoth01_GimicStart = true;

			UE_LOG(LogTemp, Warning, TEXT("Golem Fourth_fisrt Gimic Start"));
			FothGimic();

			//Pause Snd Gimic Timer
			GetWorld()->GetTimerManager().ClearTimer(SndGimicTimerHandle);
		}
		//Fouth_Gimic_02 Start
		if (GetBossCurrentHp() <= GetBossMaxHp() * (FothGimic_02_StartHp / 100) && !isFoth02_GimicStart)
		{
			isFoth02_GimicStart = true;

			UE_LOG(LogTemp, Warning, TEXT("Golem Fourth_Second Gimic Start"));
			FothGimic();

			//Pause Snd Gimic Timer
			GetWorld()->GetTimerManager().ClearTimer(SndGimicTimerHandle);
		}
	}
	return 0.0f;
}

//float ABoss_Golem::CalculateForwardVector(float forwardVector)
//{
//	if (forwardVector >= 0)
//	{
//		return 1.f;
//	}
//	else return -1.f;
//}

void ABoss_Golem::Golem_Destroy()
{
	Destroy();
}

void ABoss_Golem::OnRangeOverlapBegin(UPrimitiveComponent* const OverlappedComponent,
	AActor* const otherActor, UPrimitiveComponent* const OtherComponent, 
	int const OtherBodyIndex, bool const FromSweep, FHitResult const& SweepResult)
{
	if (otherActor == this) return;

	if (otherActor->ActorHasTag("PLAYER"))
	{
		isTrdGimicCanAttack = true;
		UAIBlueprintHelperLibrary::GetAIController(this)->GetBlackboardComponent()->SetValueAsBool("PlayerIsInMeleeRange", true);
	}
}

void ABoss_Golem::OnRangeOverlapEnd(UPrimitiveComponent* const OverlappedComponent, 
	AActor* const otherActor, UPrimitiveComponent* const OtherComponent, int const OtherBodyIndex)
{
	if (otherActor == this) return;

	if (otherActor->ActorHasTag("PLAYER"))
	{
		isTrdGimicCanAttack = false;
		UAIBlueprintHelperLibrary::GetAIController(this)->GetBlackboardComponent()->SetValueAsBool("PlayerIsInMeleeRange", false);
	}
}

void ABoss_Golem::FstGimic_Implementation()
{
	//Start Gimic Sub Tree
	UAIBlueprintHelperLibrary::GetAIController(this)->GetBlackboardComponent()->SetValueAsBool("isGimic", true);
	UAIBlueprintHelperLibrary::GetAIController(this)->GetBlackboardComponent()->SetValueAsBool("IsTimeGimic", false);
	UAIBlueprintHelperLibrary::GetAIController(this)->GetBlackboardComponent()->SetValueAsBool("FirstGimic", true); 
	UAIBlueprintHelperLibrary::GetAIController(this)->GetBlackboardComponent()->SetValueAsBool("IsFstGimicING", true);
}

void ABoss_Golem::SndGimic_Implementation()
{
	//SetInvincible(true);
	//UAIBlueprintHelperLibrary::GetAIController(this)->GetBlackboardComponent()->SetValueAsBool("isGimic", true);
	//UAIBlueprintHelperLibrary::GetAIController(this)->GetBlackboardComponent()->SetValueAsBool("IsTimeGimic", true);
}

void ABoss_Golem::SetSndGimicTimer()
{
	GetWorld()->GetTimerManager().SetTimer(SndGimicTimerHandle, this, &ABoss_Golem::SndGimic, SndGimicDelay, true);
}

void ABoss_Golem::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}