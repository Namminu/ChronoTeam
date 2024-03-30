// Fill out your copyright notice in the Description page of Project Settings.


#include "Base_Boss.h"
#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
ABase_Boss::ABase_Boss()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Attack Range Collision Setup
	AttackRange = CreateDefaultSubobject<USphereComponent>(TEXT("Attack Range Collision"));
	AttackRange->SetupAttachment(GetMesh());
	//Weapon Hitbox Collision Setup
	WeaponRange = CreateDefaultSubobject<UBoxComponent>(TEXT("Weapon Hit Box"));
	WeaponRange->SetupAttachment(GetMesh());


}

// Called when the game starts or when spawned
void ABase_Boss::BeginPlay()
{
	Super::BeginPlay();
	
	//Initialize Currnet Boss Hp to Max Hp
	f_bossCurrentHp = f_bossMaxHp;

	//Setup Event Bind to Collision Box
	AttackRange->OnComponentBeginOverlap.AddDynamic(this, &ABase_Boss::OnRangeOverlapBegin);
	AttackRange->OnComponentEndOverlap.AddDynamic(this, &ABase_Boss::OnRangeOverlapEnd);
	WeaponRange->OnComponentBeginOverlap.AddDynamic(this, &ABase_Boss::OnAttackOverlapBegin);
	WeaponRange->OnComponentEndOverlap.AddDynamic(this, &ABase_Boss::OnAttackOverlapEnd);
}

// Called every frame
void ABase_Boss::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABase_Boss::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

int ABase_Boss::MeleeAttack_Implementation()
{
	return 0;
}

void ABase_Boss::Boss_Death_Implementation()
{
}

float ABase_Boss::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	SetBossCurrentHp(GetBossCurrentHp()-DamageAmount);

	if (GetBossCurrentHp() <= 0) Boss_Death_Implementation();

	return 0.0f;
}

void ABase_Boss::OnAttackOverlapBegin(UPrimitiveComponent* const OverlappedComponent,
	AActor* const otherActor, UPrimitiveComponent* const OtherComponent, 
	int const OtherBodyIndex, bool const FromSweep, FHitResult const& SweepResult)
{
}

void ABase_Boss::OnAttackOverlapEnd(UPrimitiveComponent* const OverlappedComponent,
	AActor* const otherActor, UPrimitiveComponent* const OtherComponent, int const OtherBodyIndex)
{
}

void ABase_Boss::OnRangeOverlapBegin(UPrimitiveComponent* const OverlappedComponent,
	AActor* const otherActor, UPrimitiveComponent* const OtherComponent, 
	int const OtherBodyIndex, bool const FromSweep, FHitResult const& SweepResult)
{
}

void ABase_Boss::OnRangeOverlapEnd(UPrimitiveComponent* const OverlappedComponent,
	AActor* const otherActor, UPrimitiveComponent* const OtherComponent, int const OtherBodyIndex)
{
}

