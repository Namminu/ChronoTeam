// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseMonster.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include <TeamChrono/TeamChronoCharacter.h>
#include "AI_Controller_.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"

// Sets default values
ABaseMonster::ABaseMonster() : WeaponCollisionBox{ CreateDefaultSubobject<UBoxComponent>(TEXT("WeaponCollisionBox")) }
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (WeaponCollisionBox)	//Weapon ��Ʈ�ڽ� ����
	{
		WeaponCollisionBox->SetBoxExtent(FVector(5.f));
		FAttachmentTransformRules const Rules{
			EAttachmentRule::SnapToTarget,	//location
			EAttachmentRule::SnapToTarget,	//rotation
			EAttachmentRule::KeepWorld,		//World Scale
			false	// Not default Attach to body
		};
		WeaponCollisionBox->AttachToComponent(GetMesh(), Rules, "hand_r_Socket");
		WeaponCollisionBox->SetRelativeLocation(FVector(-7.f, 0.f, 0.f));
	}
}

// Called when the game starts or when spawned
void ABaseMonster::BeginPlay()
{
	Super::BeginPlay();

	arrow_Distance = 6000.f;

	//Create Dynamic Material Instance
	CreateMTI();

	//���� �ʱ� ü�� �ʱ�ȭ
	monNowHp = monMaxHp;

	WeaponCollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ABaseMonster::OnAttackOverlapBegin);
	WeaponCollisionBox->OnComponentEndOverlap.AddDynamic(this, &ABaseMonster::OnAttackOverlapEnd);
	
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
		//auto const NewHealth = Enemy->GetHealth() - Enemy->GetMaxHealth() * 0.1f;
		//Enemy->SetHealth(NewHealth);
	
		UE_LOG(LogTemp, Warning, TEXT("Monster hit Player"));
	}
}

void ABaseMonster::OnAttackOverlapEnd(UPrimitiveComponent* const OverlappedComponent, 
	AActor* const otherActor, 
	UPrimitiveComponent* const OtherComponent, 
	int const OtherBodyIndex)
{

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

void ABaseMonster::AttackStart() const
{
	WeaponCollisionBox->SetCollisionProfileName("Fist");
	WeaponCollisionBox->SetNotifyRigidBodyCollision(true);
	WeaponCollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	UE_LOG(LogTemp, Error, TEXT("Attack Start"));
}

void ABaseMonster::AttackEnd() const
{
	WeaponCollisionBox->SetCollisionProfileName("Fist");
	WeaponCollisionBox->SetNotifyRigidBodyCollision(false);
	WeaponCollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

	UE_LOG(LogTemp, Error, TEXT("Attack End"));
}

void ABaseMonster::FireArrow() const
{
	UE_LOG(LogTemp, Warning, TEXT("Achor Launch Arrow"));


}

float ABaseMonster::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	DamageFlash();

	////������ŭ ��¦�� �ݺ�
	//for (int i = 0; i < flashCount; i++)
	//{
	//	UE_LOG(LogTemp, Error, TEXT("Damage Flash Count : %d"), i+1);
	//	DamageFlash();
	//}

	monNowHp -= DamageAmount;	//���� ���� ��ŭ ü�� ����
	if (monNowHp <= 0)	//���� ü���� 0 �̸��� ��� ��� �Լ� ȣ��
	{
		mon_Death();
	}

	return DamageAmount;
}

void ABaseMonster::AttachWeapon(TSubclassOf<AMonster_Weapon> Weapon, FName socketName)
{
	//AMonster_Weapon* monsterWP
	WeaponInstance = GetWorld()->SpawnActor<AMonster_Weapon>(Weapon, GetMesh()->GetSocketTransform(socketName, ERelativeTransformSpace::RTS_World));

	WeaponInstance->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, socketName);
}

void ABaseMonster::mon_Death()
{
	AAI_Controller_* monsterAI = Cast<AAI_Controller_>(GetController());
	monsterAI->StopAI();	//Stop BT 
	GetCharacterMovement()->SetMovementMode(MOVE_None);	//Stop Movement
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);	//Can't Collision
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);	

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

UAnimMontage* ABaseMonster::GetAtkMontage() const
{ 
	return AtkMontage; 
}

UBehaviorTree* ABaseMonster::GetBehaviorTree() const
{ 
	return BTree;
}