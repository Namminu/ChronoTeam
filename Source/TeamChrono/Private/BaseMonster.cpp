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

// Sets default values
ABaseMonster::ABaseMonster()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//if (WeaponCollisionBox)	//Weapon ��Ʈ�ڽ� ����
	//{
	//	//WeaponCollisionBox->SetBoxExtent(FVector(5.f));
	//	//FAttachmentTransformRules const Rules{
	//	//	EAttachmentRule::SnapToTarget,	//location
	//	//	EAttachmentRule::SnapToTarget,	//rotation
	//	//	EAttachmentRule::KeepWorld,		//World Scale
	//	//	false	// Not default Attach to body
	//	//};
	//	//WeaponCollisionBox->AttachToComponent(GetMesh(), Rules, "hand_r_Socket");
	//}

	//WeaponCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Weapon Collision Box"));
	//WeaponCollisionBox->SetupAttachment(GetMesh());

	//Attack Range - Capsule Component Setup
	AttackRangeBox = CreateDefaultSubobject<USphereComponent>(TEXT("Attack Range Box"));
	AttackRangeBox->SetupAttachment(GetCapsuleComponent());

	//Niagara Effect Component
	NiagaraAttackEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Attack Effect"));
	NiagaraAttackEffect->SetupAttachment(GetCapsuleComponent());
}

// Called when the game starts or when spawned  
void ABaseMonster::BeginPlay()
{
	Super::BeginPlay();

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

	//if (WeaponCollisionBox != nullptr)
	//{
	//	WeaponCollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ABaseMonster::OnAttackOverlapBegin);
	//	//WeaponCollisionBox->OnComponentEndOverlap.AddDynamic(this, &ABaseMonster::OnAttackOverlapEnd);
	//}
	//else UE_LOG(LogTemp, Error, TEXT("Weapon Collision Box is NULL"));

	if (AttackRangeBox != nullptr)
	{
		AttackRangeBox->OnComponentBeginOverlap.AddDynamic(this, &ABaseMonster::OnRangeOverlapBegin);
		AttackRangeBox->OnComponentEndOverlap.AddDynamic(this, &ABaseMonster::OnRangeOverlapEnd);
	}
	else UE_LOG(LogTemp, Error, TEXT("Attack Range Box is NULL"));

	//���� �� ���� ������ ä�� ����
	//AttachWeapon(monsterWeapon, "Weapon_R");

	//���� �� �ִϸ��̼� ���
	Change_Opacity(0,1);
	PlayAnimMontage(CreateMontage);
}

void ABaseMonster::OnAttackOverlapBegin(UPrimitiveComponent* const OverlappedComponent,
	AActor* const otherActor,
	UPrimitiveComponent* const OtherComponent,
	int const OtherBodyIndex, bool const FromSweep,
	FHitResult const& SweepResult)
{
	if (otherActor == this) return;		//��Ʈ�ڽ��� �ڱ� �ڽſ��� ����� ��� �ƹ� ����x

	if (otherActor->ActorHasTag("PLAYER"))	//��Ʈ�ڽ��� �÷��̾�� ����� ��� = �÷��̾� ���� ��
	{
		UE_LOG(LogTemp, Warning, TEXT("Monster hit Player"));

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

	if (otherActor->ActorHasTag("PLAYER"))
	{
		UAIBlueprintHelperLibrary::GetAIController(this)->GetBlackboardComponent()->SetValueAsBool("PlayerIsInMeleeRange", true);
		//UE_LOG(LogTemp, Warning, TEXT("Player in Range set True"));
	}

}

void ABaseMonster::OnRangeOverlapEnd(UPrimitiveComponent* const OverlappedComponent,
	AActor* const otherActor,
	UPrimitiveComponent* const OtherComponent,
	int const OtherBodyIndex)
{
	if (otherActor->ActorHasTag("PLAYER"))
	{
		UAIBlueprintHelperLibrary::GetAIController(this)->GetBlackboardComponent()->SetValueAsBool("PlayerIsInMeleeRange", false);
		//UE_LOG(LogTemp, Warning, TEXT("Player in Range set False"));
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
	UE_LOG(LogTemp, Error, TEXT("Monster get attack"));
	if (AtkMontage)
	{
		PlayAnimMontage(AtkMontage);
	}
	return 0;
}

void ABaseMonster::AttackStart() const
{
	//WeaponCollisionBox->SetCollisionProfileName("Fist");
	//WeaponCollisionBox->SetNotifyRigidBodyCollision(true);
	//WeaponCollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

	UE_LOG(LogTemp, Error, TEXT("Attack Start"));
}

//void ABaseMonster::AttackEnd() const
//{
//	WeaponCollisionBox->SetCollisionProfileName("Fist");
//	WeaponCollisionBox->SetNotifyRigidBodyCollision(false);
//	WeaponCollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
//
//	UE_LOG(LogTemp, Error, TEXT("Attack End"));
//}

float ABaseMonster::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (GetIsBorn())
	{
		monNowHp -= DamageAmount;	//���� ���� ��ŭ ü�� ����
		if (monNowHp <= 0)	//���� ü���� 0 �̸��� ��� ��� �Լ� ȣ��
		{
			isMonsterLive = false;
			mon_Death();
			return DamageAmount;
		}
		UE_LOG(LogTemp, Warning, TEXT("BaseMonster Take Damage"));
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
	//Stop all Montages Before Death
	GetMesh()->GetAnimInstance()->StopAllMontages(NULL);

	//Stop Movement
	GetCharacterMovement()->SetMovementMode(MOVE_None);	
	//Stop Collision
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);	
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);	
	GetAttackRangeColl()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//GetWeaponColl()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

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
}

void ABaseMonster::CreateMTI()
{
	//Get 1st Material Instance
	Fst_MTI = GetMesh()->CreateDynamicMaterialInstance(0);
	if (Fst_MTI != nullptr)
	{
		MTIArray.Add(Fst_MTI);

		/*		���� �ڵ� ���� �� ���� �ٶ�
		* 
		* 		FLinearColor Fst_Init_Color;	//Fst_Init_~�� Fst_MTI�� �ʱⰪ�� �����ϰ��� ��
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