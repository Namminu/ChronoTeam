// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseMonster.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include <TeamChrono/TeamChronoCharacter.h>
#include "AI_Controller_.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include <Kismet/GameplayStatics.h>
#include "Achor_Arrow.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "BehaviorTree/BlackboardComponent.h"
#include <Blueprint/AIBlueprintHelperLibrary.h>
#include "Monster_Weapon.h"
#include <Kismet/KismetMathLibrary.h>

// Sets default values
ABaseMonster::ABaseMonster()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Attack Range - Capsule Component Setup
	AttackRangeBox = CreateDefaultSubobject<USphereComponent>(TEXT("Attack Range Box"));
	AttackRangeBox->SetupAttachment(GetCapsuleComponent());

	//Niagara Effect Component
	NiagaraAttackEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Attack Effect"));
	NiagaraAttackEffect->SetupAttachment(GetCapsuleComponent());
}

void ABaseMonster::InitFunc()
{
	SetActorTickEnabled(false);
	//SetMonsterCanFight(false);

	AttackRangeBox->OnComponentBeginOverlap.RemoveDynamic(this, &ABaseMonster::OnRangeOverlapBegin);
	AttackRangeBox->OnComponentEndOverlap.RemoveDynamic(this, &ABaseMonster::OnRangeOverlapEnd);

	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetAttackRangeColl()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	//Stop all Montages Before Death
	GetMesh()->GetAnimInstance()->StopAllMontages(NULL);

	//Stop BT 
	if (AAI_Controller_* monsterAI = Cast<AAI_Controller_>(GetController()))
	{
		monsterAI->StopAI();
	}
	else UE_LOG(LogTemp, Error, TEXT("Base Monster Cast Failed to AI_Controller"));

	DetachFromControllerPendingDestroy();
}

// Called when the game starts or when spawned  
void ABaseMonster::BeginPlay()
{
	Super::BeginPlay();

	player = Cast<ATeamChronoCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	if (!player) UE_LOG(LogTemp, Error, TEXT("Cast Failed to Player in BaseMonster"));

	//Begin With Deactivate Niagara Effect
	if (GetAttackEffect() != nullptr)
	{
		GetAttackEffect()->Deactivate();
	}

	//Setup How Collision Enable
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	//GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetAttackRangeColl()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	//GetWeaponColl()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	//Create Dynamic Material Instance
	CreateMTI();
	
	monNowHp = monMaxHp;
	monAtk = 1;
	isMonsterBorn = false; 
	isMonsterLive = true;

	isUnDamaged = true;

	IsCanFight = true;

	if (AttackRangeBox != nullptr)
	{
		AttackRangeBox->OnComponentBeginOverlap.AddDynamic(this, &ABaseMonster::OnRangeOverlapBegin);
		AttackRangeBox->OnComponentEndOverlap.AddDynamic(this, &ABaseMonster::OnRangeOverlapEnd);
	}
	else UE_LOG(LogTemp, Error, TEXT("Attack Range Box is NULL"));

	//시작 시 애니메이션 재생
	Change_Opacity(0,1);
	PlayAnimMontage(CreateMontage);
}

void ABaseMonster::OnAttackOverlapBegin(UPrimitiveComponent* const OverlappedComponent,
	AActor* const otherActor,
	UPrimitiveComponent* const OtherComponent,
	int const OtherBodyIndex, bool const FromSweep,
	FHitResult const& SweepResult)
{
	if (otherActor == this) return;		//히트박스가 자기 자신에게 닿았을 경우 아무 영향x

	if (otherActor->ActorHasTag("PLAYER"))	//히트박스가 플레이어에게 닿았을 경우 = 플레이어 공격 시
	{
		UGameplayStatics::ApplyDamage(otherActor, monAtk, nullptr, this, DamageType);
	}
}

void ABaseMonster::OnAttackOverlapEnd(UPrimitiveComponent* const OverlappedComponent, 
	AActor* const otherActor, 
	UPrimitiveComponent* const OtherComponent, 
	int const OtherBodyIndex)
{

}

void ABaseMonster::OnRangeOverlapBegin(UPrimitiveComponent* const OverlappedComponent,
	AActor* const otherActor, UPrimitiveComponent* const OtherComponent,
	int const OtherBodyIndex, bool const FromSweep,
	FHitResult const& SweepResult)
{
	if (otherActor == this) return;

	if (otherActor && otherActor->ActorHasTag("PLAYER"))
	{
		UAIBlueprintHelperLibrary::GetAIController(this)->GetBlackboardComponent()->SetValueAsBool("PlayerIsInMeleeRange", true);
	}

}

void ABaseMonster::OnRangeOverlapEnd(UPrimitiveComponent* const OverlappedComponent,
	AActor* const otherActor,
	UPrimitiveComponent* const OtherComponent,
	int const OtherBodyIndex)
{
	if (otherActor && otherActor->ActorHasTag("PLAYER"))
	{
		UAIBlueprintHelperLibrary::GetAIController(this)->GetBlackboardComponent()->SetValueAsBool("PlayerIsInMeleeRange", false);
	}
}

// Called every frame
void ABaseMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseMonster::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

int ABaseMonster::MeleeAttack_Implementation()
{
	if (AtkMontage)
	{
		PlayAnimMontage(AtkMontage);
	}
	return 0;
}

float ABaseMonster::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (GetIsBorn())
	{
		if (isUnDamaged)
		{
			UAIBlueprintHelperLibrary::GetAIController(this)->GetBlackboardComponent()->SetValueAsBool("IsFirstDamaged", true);
			isUnDamaged = false;
		}

		monNowHp -= DamageAmount;	//피해 입은 만큼 체력 감소
		if (monNowHp <= 0)	//몬스터 체력이 0 미만일 경우 사망 함수 호출
		{
			isMonsterLive = false;
			mon_Death();
			return DamageAmount;
		}
		DamageFlash();
	}
	return DamageAmount;
}

void ABaseMonster::AttachWeapon(TSubclassOf<AMonster_Weapon> Weapon, FName socketName)
{
	//AMonster_Weapon* monsterWP	
	WeaponInstance = GetWorld()->SpawnActor<AMonster_Weapon>(Weapon, GetMesh()->GetSocketTransform(socketName, ERelativeTransformSpace::RTS_World));
	WeaponInstance->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, socketName);
}

void ABaseMonster::CallNiagaraEffect(UNiagaraComponent* NiaEffect)
{
	if (NiaEffect != nullptr)
	{
		NiaEffect->Activate();
	}
}

void ABaseMonster::mon_Death_Implementation()
{
	IsCanFight = false;

	//BroadCast Monster Die Event
	MonsterDie.Broadcast();

	//Stop all Montages Before Death
	GetMesh()->GetAnimInstance()->StopAllMontages(NULL);

	//Stop Movement
	GetCharacterMovement()->SetMovementMode(MOVE_None);	
	//Stop Collision
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);	
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);	
	GetAttackRangeColl()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	AAI_Controller_* monsterAI = Cast<AAI_Controller_>(GetController());
	monsterAI->StopAI();	//Stop BT 
	DetachFromControllerPendingDestroy();

	PlayAnimMontage(DeathMontage);	//Death Animation	
	Change_Opacity(1, 0);	//Change Opacity to 1 -> 0

	FTimerHandle TimerHandle;
	float delay = 3.3f;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ABaseMonster::mon_Destroy, delay, false);	//Destory Actor After DeathDelay
}

void ABaseMonster::mon_Destroy()
{
	Destroy();
	WeaponInstance->Destroy();
}

void ABaseMonster::CreateMTI()
{
	//Get 1st Material Instance
	Fst_MTI = GetMesh()->CreateDynamicMaterialInstance(0);
	if (Fst_MTI != nullptr)
	{
		MTIArray.Add(Fst_MTI);

		/*		추후 코드 수정 시 참고 바람
		* 
		* 		FLinearColor Fst_Init_Color;	//Fst_Init_~에 Fst_MTI의 초기값을 저장하고자 함
		Fst_MTI->GetVectorParameterValue(FName("EmissiveColor"), Fst_Init_Color);
		float Fst_Init_Multiplier;
		Fst_MTI->GetScalarParameterValue(FName("EmissiveMutiplier"), Fst_Init_Multiplier);

		*/
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("First Material is null"));
	}
	
	//Get 2nd Material Instance
	Snd_MTI = GetMesh()->CreateDynamicMaterialInstance(1);
	if (Snd_MTI != nullptr)
	{
		MTIArray.Add(Snd_MTI);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Second Material is null"));
	}
}

void ABaseMonster::PlayMontage(UAnimMontage* Montage)
{
	PlayAnimMontage(Montage);
}

UAnimMontage* ABaseMonster::GetAtkMontage() const
{ 
	return AtkMontage; 
}
UAnimMontage* ABaseMonster::GetCreateMontage() const
{
	return CreateMontage;
}

UAnimMontage* ABaseMonster::GetDeathMontage() const
{
	return DeathMontage;
}

UBehaviorTree* ABaseMonster::GetBehaviorTree() const
{
	return BTree;
}