// Fill out your copyright notice in the Description page of Project Settings.


#include "Base_Boss.h"
#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include <Kismet/GameplayStatics.h>
#include "AI_Controller_.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ABase_Boss::ABase_Boss()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Attack Range Collision Setup
	AttackRange = CreateDefaultSubobject<USphereComponent>(TEXT("Attack Range Collision"));
	AttackRange->SetupAttachment(GetCapsuleComponent());
	//Weapon Hitbox Collision Setup
	//WeaponCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Weapon Hit Box"));
	//WeaponCollision->SetupAttachment(GetMesh());


}

// Called when the game starts or when spawned
void ABase_Boss::BeginPlay()
{
	Super::BeginPlay();
	
	//Save Boss Init Max Walk Speed
	f_bossInitSpeed = GetCharacterMovement()->MaxWalkSpeed;

	//Cast to Player
	player = Cast<ATeamChronoCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (!player) UE_LOG(LogTemp, Error, TEXT("Cast Failed to Player in Base_Boss"));

	//Initialize Currnet Boss Hp to Max Hp
	f_bossCurrentHp = f_bossMaxHp;

	//Setup Event Bind to Collision Box
	AttackRange->OnComponentBeginOverlap.AddDynamic(this, &ABase_Boss::OnRangeOverlapBegin);
	AttackRange->OnComponentEndOverlap.AddDynamic(this, &ABase_Boss::OnRangeOverlapEnd);
	//WeaponCollision->OnComponentBeginOverlap.AddDynamic(this, &ABase_Boss::OnAttackOverlapBegin);
	//WeaponCollision->OnComponentEndOverlap.AddDynamic(this, &ABase_Boss::OnAttackOverlapEnd);
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

void ABase_Boss::SetFlashMTI_Implementation(UMaterialInstanceDynamic* MT)
{
	if (MT)
	{
		MTIArray.Add(MT);
	}
}

void ABase_Boss::Boss_Death_Implementation()
{
	//Stop Movement
	GetCharacterMovement()->SetMovementMode(MOVE_None);
	//Stop BT 
	AAI_Controller_* monsterAI = Cast<AAI_Controller_>(GetController());
	monsterAI->StopAI();
}

//void ABase_Boss::FocusOnPlayer_Implementation(ATeamChronoCharacter* mainPlayer)
//{
//	if(mainPlayer)
//	{
//		AAI_Controller_* monsterAI = Cast<AAI_Controller_>(GetController());
//		monsterAI->SetFocus(mainPlayer);
//	}
//}

float ABase_Boss::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	SetBossCurrentHp(GetBossCurrentHp()-DamageAmount);

	if (GetBossCurrentHp() <= 0) Boss_Death_Implementation();

	return 0.0f;
}

//void ABase_Boss::OnAttackOverlapBegin(UPrimitiveComponent* const OverlappedComponent,
//	AActor* const otherActor, UPrimitiveComponent* const OtherComponent, 
//	int const OtherBodyIndex, bool const FromSweep, FHitResult const& SweepResult)
//{
//}

//void ABase_Boss::OnAttackOverlapEnd(UPrimitiveComponent* const OverlappedComponent,
//	AActor* const otherActor, UPrimitiveComponent* const OtherComponent, int const OtherBodyIndex)
//{
//}

void ABase_Boss::OnRangeOverlapBegin(UPrimitiveComponent* const OverlappedComponent,
	AActor* const otherActor, UPrimitiveComponent* const OtherComponent, 
	int const OtherBodyIndex, bool const FromSweep, FHitResult const& SweepResult)
{
}

void ABase_Boss::OnRangeOverlapEnd(UPrimitiveComponent* const OverlappedComponent,
	AActor* const otherActor, UPrimitiveComponent* const OtherComponent, int const OtherBodyIndex)
{
}

//void ABase_Boss::EndPlay(const EEndPlayReason::Type EndPlayReason)
//{
//	Super::EndPlay(EndPlayReason);
//}