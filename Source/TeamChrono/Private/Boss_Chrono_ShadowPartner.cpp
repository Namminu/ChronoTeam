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

	SetMTI();
	ChangeOpacity(0, 1);
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
	if (CurrentAttackCount < LifeAttackCount)
	{
		CurrentAttackCount++;
		AttackFunc(GetRandomAttackNum(0, 2));
	}
	else if (CurrentAttackCount >= LifeAttackCount)
	{
		ChangeOpacity(1, 0);
	}

	return 0;
}

void ABoss_Chrono_ShadowPartner::Boss_Death_Implementation()
{

}

void ABoss_Chrono_ShadowPartner::AttackFunc_Implementation(int caseNum)
{
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
	UE_LOG(LogTemp, Error, TEXT("%d"), num);
	return num;
}

void ABoss_Chrono_ShadowPartner::SetMTI()
{
	MTI = GetMesh()->CreateDynamicMaterialInstance(0);
}

void ABoss_Chrono_ShadowPartner::SetAttackTimer()
{
	GetWorld()->GetTimerManager().SetTimer(ShapaAttackTimer, this, &ABoss_Chrono_ShadowPartner::CallAttackBB, ShapaAttackDelay, true);
}

void ABoss_Chrono_ShadowPartner::ResetAttackTimer()
{
	GetWorld()->GetTimerManager().ClearTimer(ShapaAttackTimer);
}

void ABoss_Chrono_ShadowPartner::CallAttackBB()
{
	UAIBlueprintHelperLibrary::GetAIController(this)->GetBlackboardComponent()->SetValueAsBool("IsAttack", true);
}
