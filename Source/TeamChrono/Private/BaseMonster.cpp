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

	if (WeaponCollisionBox)	//Weapon 히트박스 설정
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

	//몬스터 초기 체력 초기화
	monNowHp = monMaxHp;

	WeaponCollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ABaseMonster::OnAttackOverlapBegin);
	WeaponCollisionBox->OnComponentEndOverlap.AddDynamic(this, &ABaseMonster::OnAttackOverlapEnd);
	
	//시작 시 무기 소지한 채로 시작
	//AttachWeapon(monsterWeapon, "Weapon_R");

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

	////변수만큼 반짝임 반복
	//for (int i = 0; i < flashCount; i++)
	//{
	//	UE_LOG(LogTemp, Error, TEXT("Damage Flash Count : %d"), i+1);
	//	DamageFlash();
	//}

	monNowHp -= DamageAmount;	//피해 입은 만큼 체력 감소
	if (monNowHp <= 0)	//몬스터 체력이 0 미만일 경우 사망 함수 호출
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

UAnimMontage* ABaseMonster::GetAtkMontage() const
{ 
	return AtkMontage; 
}

UBehaviorTree* ABaseMonster::GetBehaviorTree() const
{ 
	return BTree;
}