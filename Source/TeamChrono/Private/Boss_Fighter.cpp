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

// Setup Flash MTI
	SetFullFMTI();

}

void ABoss_Fighter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABoss_Fighter::DamageFlash_Implementation()
{
	GetBossWeapon()->DamageFlash();
}

int ABoss_Fighter::MeleeAttack_Implementation()
{


	return 0;
}

void ABoss_Fighter::Boss_Death_Implementation()
{
	Super::Boss_Death_Implementation();

}

float ABoss_Fighter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	DamageFlash();

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

	UE_LOG(LogTemp, Error, TEXT("%s : clear to Setup Flash MT"), *skeleton->GetName());
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