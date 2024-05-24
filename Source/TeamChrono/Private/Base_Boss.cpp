// Fill out your copyright notice in the Description page of Project Settings.


#include "Base_Boss.h"
#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include <Kismet/GameplayStatics.h>
#include "BossAIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include <Blueprint/AIBlueprintHelperLibrary.h>
#include "BehaviorTree/BlackboardComponent.h"
#include "Base_BossWeapon.h"

// Sets default values
ABase_Boss::ABase_Boss()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Attack Range Collision Setup
	AttackRange = CreateDefaultSubobject<USphereComponent>(TEXT("Attack Range Collision"));
	AttackRange->SetupAttachment(GetCapsuleComponent());

}

// Called when the game starts or when spawned
void ABase_Boss::BeginPlay()
{
	Super::BeginPlay();
	
	//Cast to Custom Game Instance
	myGameInstance = Cast<UGI_Chrono>(GetGameInstance());

	BeginLocation = GetActorLocation();

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
	if (ABossAIController* BossAI = Cast<ABossAIController>(GetController()))
	{
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(BossAI, this->GetActorLocation());
	}

	return 0;
}

void ABase_Boss::AttackFunc_Implementation(int caseNum)
{
}

void ABase_Boss::SetFocusToPlayer()
{
	if (ABossAIController* BossAI = Cast<ABossAIController>(GetController()))
	{
		BossAI->SetFocus(player);
	}
}

void ABase_Boss::ClearFocusToPlayer()
{
	if (ABossAIController* BossAI = Cast<ABossAIController>(GetController()))
	{
		BossAI->ClearFocus(EAIFocusPriority::Default);
	}
}

void ABase_Boss::AttachWeapon(TSubclassOf<ABase_BossWeapon> Weapon, FName WeaponSocket)
{
	weaponInstance = GetWorld()->SpawnActor<ABase_BossWeapon>(Weapon, GetMesh()->GetSocketTransform(WeaponSocket, ERelativeTransformSpace::RTS_World));
	weaponInstance->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, WeaponSocket);
}

void ABase_Boss::DetachWeapon()
{
	weaponInstance->Destroy();
}

void ABase_Boss::PlayMontage(UAnimMontage* Montage)
{
	GetMesh()->GetAnimInstance()->Montage_Play(Montage);
}

void ABase_Boss::SetFlashMTIArray_Implementation(UMaterialInstanceDynamic* MT)
{
	if (MT)
	{
		MTIArray.Add(MT);
	}
}

void ABase_Boss::Boss_Death_Implementation()
{
	//BroadCast Boss Monster Die Event
	BossMonsterDie.Broadcast();

	//Stop all Montages Before Death
	GetMesh()->GetAnimInstance()->StopAllMontages(NULL);

	//Stop Movement
	GetCharacterMovement()->SetMovementMode(MOVE_None);
	//Set Collision to NoCollision
	GetAttackRangeColl()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	//Stop BT 
	ABossAIController* BossAI = Cast<ABossAIController>(GetController());
	BossAI->StopAI();

	//Stop Tick
	SetActorTickEnabled(false);

	//Set Death Property
	bIsDie = true;

	//Set Boss Hp UI Off
	SetOffWZ();
}

void ABase_Boss::InitFunc_Implementation(FVector FirstLocation)
{
	SetActorTickEnabled(false);
	SetIsCanFight(false);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetAttackRangeColl()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	//Stop all Montages Before Death
	GetMesh()->GetAnimInstance()->StopAllMontages(NULL);

	//Stop BT 
	ABossAIController* BossAI = Cast<ABossAIController>(GetController());
	BossAI->StopAI();
}

float ABase_Boss::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent,
	AController* EventInstigator, AActor* DamageCauser)
{
	SetBossCurrentHp(GetBossCurrentHp() - DamageAmount);
	UpdateHpPercent();
	if (GetBossCurrentHp() <= 0) Boss_Death_Implementation();
	return 0.0f;
}

void ABase_Boss::DamageFlash_Implementation()
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