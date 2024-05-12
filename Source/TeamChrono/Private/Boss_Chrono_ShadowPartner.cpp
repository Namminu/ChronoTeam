// Fill out your copyright notice in the Description page of Project Settings.


#include "Boss_Chrono_ShadowPartner.h"
#include <Blueprint/AIBlueprintHelperLibrary.h>
#include "BossAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"

ABoss_Chrono_ShadowPartner::ABoss_Chrono_ShadowPartner()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	sk_Halo = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Halo"));
	sk_Halo->SetupAttachment(GetMesh());
	sk_Halo->SetLeaderPoseComponent(GetMesh());

	coll_Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Coll"));
	coll_Box->SetupAttachment(GetCapsuleComponent());
}

void ABoss_Chrono_ShadowPartner::BeginPlay()
{
	Super::BeginPlay();

	CurrentAttackCount = 0;
	shapa_OrbitFinish = false;
}

void ABoss_Chrono_ShadowPartner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABoss_Chrono_ShadowPartner::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

}

int ABoss_Chrono_ShadowPartner::MeleeAttack_Implementation()
{
	CurrentAttackCount++;
	AttackFunc(GetRandomAttackNum(0, 2));

	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ABoss_Chrono_ShadowPartner::CheckDisappearTime_Implementation, 4.f, false);
	return 0;
}

void ABoss_Chrono_ShadowPartner::Boss_Death_Implementation()
{

}

void ABoss_Chrono_ShadowPartner::AttackFunc_Implementation(int caseNum)
{
}

void ABoss_Chrono_ShadowPartner::SetupCenterArrow(AActor* centerArrow)
{
	CenterArrow = centerArrow;
}

void ABoss_Chrono_ShadowPartner::TempAttachPin(TSubclassOf<AChrono_JustMeshPin> Weapon, FName WeaponSocket)
{
	class AChrono_JustMeshPin* ClockPin;
	ClockPin = GetWorld()->SpawnActor<AChrono_JustMeshPin>(Weapon, GetMesh()->GetSocketTransform(WeaponSocket, ERelativeTransformSpace::RTS_World));
	ClockPin->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, WeaponSocket);
	ClockPinArray.AddUnique(ClockPin);
}

int ABoss_Chrono_ShadowPartner::GetRandomAttackNum(int min, int max)
{
	int num = FMath::RandRange(min, max);
	return num;
}

void ABoss_Chrono_ShadowPartner::SetMTI()
{
	UMaterialInstanceDynamic* FstMT = GetMesh()->CreateDynamicMaterialInstance(0);
	SetFlashMTIArray(FstMT);

	UMaterialInstanceDynamic* SndMT = sk_Halo->CreateDynamicMaterialInstance(0);
	SetFlashMTIArray(SndMT);
}

void ABoss_Chrono_ShadowPartner::SetPinMeshMTI()
{
	for (AChrono_JustMeshPin* PinMT : ClockPinArray)
	{
		if (PinMT)
		{
			UMaterialInstanceDynamic* PinMTI = PinMT->GetMesh()->CreateDynamicMaterialInstance(0);
			ClockPinMTIArray.Add(PinMTI);
		}
	}
}

void ABoss_Chrono_ShadowPartner::CheckDisappearTime_Implementation()
{
	if (CurrentAttackCount >= LifeAttackCount)
	{
		UAIBlueprintHelperLibrary::GetAIController(this)->GetBlackboardComponent()->SetValueAsBool("CanFightNow", false);
		ChangeOpacity(1, 0);
		ClockPinChangeOpacity(1, 0);
	}
}

void ABoss_Chrono_ShadowPartner::Shapa_AttackEnd()
{
	UAIBlueprintHelperLibrary::GetAIController(this)->GetBlackboardComponent()->SetValueAsBool("IsAttack", false);
	SetAttackTimer();
}

void ABoss_Chrono_ShadowPartner::SetAttackTimer()
{
	UE_LOG(LogTemp, Error, TEXT("Shapa Attack Timer Setup"));
	GetWorld()->GetTimerManager().SetTimer(ShapaAttackTimer, this, &ABoss_Chrono_ShadowPartner::CallAttackBB, ShapaAttackDelay, true);
}

void ABoss_Chrono_ShadowPartner::ResetAttackTimer()
{
	UE_LOG(LogTemp, Error, TEXT("Shapa Attack Timer Clear"));
	GetWorld()->GetTimerManager().ClearTimer(ShapaAttackTimer);
}

void ABoss_Chrono_ShadowPartner::CallAttackBB()
{
	UAIBlueprintHelperLibrary::GetAIController(this)->GetBlackboardComponent()->SetValueAsBool("IsAttack", true);
}
