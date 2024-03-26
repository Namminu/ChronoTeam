// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseElite_MagicianMonster.h"
#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"
#include <Blueprint/AIBlueprintHelperLibrary.h>
#include "AI_Controller_.h"
#include "BehaviorTree/BlackboardComponent.h"
#include <Kismet/GameplayStatics.h>

ABaseElite_MagicianMonster::ABaseElite_MagicianMonster()
{
	PrimaryActorTick.bCanEverTick = true;

	BigAttackRangeBox = CreateDefaultSubobject<USphereComponent>(TEXT("Big Attack Range"));
	BigAttackRangeBox->SetupAttachment(GetCapsuleComponent());

}

void ABaseElite_MagicianMonster::BeginPlay()
{
	Super::BeginPlay();

	//Cast to Player
	player = Cast<ATeamChronoCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	if (player == nullptr) UE_LOG(LogTemp, Error, TEXT("Magicball has Cast failed to Player"));

	isBigAck = false;

	BigAttackRangeBox->OnComponentBeginOverlap.AddDynamic(this, &ABaseElite_MagicianMonster::OnBigRangeOverlapBegin);
	BigAttackRangeBox->OnComponentEndOverlap.AddDynamic(this, &ABaseElite_MagicianMonster::OnBigRangeOverlapEnd);
	GetAttackRangeColl()->OnComponentBeginOverlap.AddDynamic(this, &ABaseElite_MagicianMonster::OnRangeOverlapBegin);
	GetAttackRangeColl()->OnComponentEndOverlap.AddDynamic(this, &ABaseElite_MagicianMonster::OnRangeOverlapEnd);
}

void ABaseElite_MagicianMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseElite_MagicianMonster::OnAttackOverlapBegin(UPrimitiveComponent* const OverlappedComponent,
	AActor* const otherActor, UPrimitiveComponent* const OtherComponent, 
	int const OtherBodyIndex, bool const FromSweep, FHitResult const& SweepResult)
{

}

void ABaseElite_MagicianMonster::OnAttackOverlapEnd(UPrimitiveComponent* const OverlappedComponent, 
	AActor* const otherActor, UPrimitiveComponent* const OtherComponent, int const OtherBodyIndex)
{
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
		isBigAck = false;
		UAIBlueprintHelperLibrary::GetAIController(this)->GetBlackboardComponent()->SetValueAsBool("isPlayerNormalRange", true);

		UE_LOG(LogTemp, Warning, TEXT("NormalAttack : True, BigAttack : false"));
	}

}

void ABaseElite_MagicianMonster::OnRangeOverlapEnd(UPrimitiveComponent* const OverlappedComponent,
	AActor* const otherActor, UPrimitiveComponent* const OtherComponent, int const OtherBodyIndex)
{
	if (otherActor == this) return;

	if (otherActor->ActorHasTag("PLAYER"))
	{
		isBigAck = true;
		UAIBlueprintHelperLibrary::GetAIController(this)->GetBlackboardComponent()->SetValueAsBool("isPlayerNormalRange", false);


		UE_LOG(LogTemp, Warning, TEXT("NormalAttack : false, BigAttack : true"));
	}

}

/// <summary>
/// 강한 공격 범위 Overlap
/// </summary>
void ABaseElite_MagicianMonster::OnBigRangeOverlapBegin(UPrimitiveComponent* const OverlappedComponent,
	AActor* const otherActor, UPrimitiveComponent* const OtherComponent,
	int const OtherBodyIndex, bool const FromSweep, FHitResult const& SweepResult)
{
	if (otherActor == this) return;

	if (otherActor->ActorHasTag("PLAYER"))
	{
		isBigAck = true;
		UAIBlueprintHelperLibrary::GetAIController(this)->GetBlackboardComponent()->SetValueAsBool("PlayerIsInAttackRange", true);
		UAIBlueprintHelperLibrary::GetAIController(this)->GetBlackboardComponent()->SetValueAsBool("isPlayerNormalRange", false);


		UE_LOG(LogTemp, Warning, TEXT("NormalAttack : false, BigAttack : true"));
	}
}

void ABaseElite_MagicianMonster::OnBigRangeOverlapEnd(UPrimitiveComponent* const OverlappedComponent,
	AActor* const otherActor, UPrimitiveComponent* const OtherComponent, int const OtherBodyIndex)
{
	if (otherActor == this) return;

	if (otherActor->ActorHasTag("PLAYER"))
	{
		isBigAck = false;
		UAIBlueprintHelperLibrary::GetAIController(this)->GetBlackboardComponent()->SetValueAsBool("PlayerIsInAttackRange", false);


		UE_LOG(LogTemp, Warning, TEXT("NormalAttack : false, BigAttack : false"));
	}
}

int ABaseElite_MagicianMonster::MeleeAttack_Implementation()
{
	Super::MeleeAttack_Implementation();

	return 0;
}

void ABaseElite_MagicianMonster::MakeBigAttack_Implementation()
{

}

float ABaseElite_MagicianMonster::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	return 0.0f;
}
