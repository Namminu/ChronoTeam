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

	//몬스터 초기 체력 초기화
	monNowHp = monMaxHp;

	WeaponCollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ABaseMonster::OnAttackOverlapBegin);
	WeaponCollisionBox->OnComponentEndOverlap.AddDynamic(this, &ABaseMonster::OnAttackOverlapEnd);
	
	//시작 시 무기 소지한 채로 시작
	AttachWeapon(monsterWeapon, "Weapon_R");

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

//bool ABaseMonster::Change_Opacity(float StartAlpha, float EndAlpha)
//{
//	//투명도 애니메이션 시작
//	SetActorHiddenInGame(true);
//	SetActorEnableCollision(false);
//	SetActorTickEnabled(false);
//
//	// 투명도 변화 시작
//	float CurrentTime = 0.0f;
//
//	TArray<UMaterialInstanceDynamic*> DynamicMaterials;
//
//	// 메시의 모든 메테리얼 인스턴스 가져오기
//	TArray<UMaterialInterface*> BaseMaterials;
//	BaseMaterials = GetMesh()->GetMaterials();
//	for (UMaterialInterface* BaseMaterial : BaseMaterials)
//	{
//		UMaterialInstanceDynamic* DynamicMaterial = UMaterialInstanceDynamic::Create(BaseMaterial, GetOwner());
//		if (DynamicMaterial)
//		{
//			DynamicMaterials.Add(DynamicMaterial);
//		}
//	}
//
//	while (CurrentTime < duration)
//	{
//		// 투명도 보간
//		float Alpha = FMath::Lerp(StartAlpha, EndAlpha, CurrentTime / duration);
//
//		// 메테리얼 인스턴스의 투명도 설정
//		for (UMaterialInstanceDynamic* DynamicMaterial : DynamicMaterials)
//		{
//			DynamicMaterial->SetScalarParameterValue(TEXT("Opacity"), Alpha);
//		}
//
//		// 경과 시간 업데이트 
//		CurrentTime += GetWorld()->GetDeltaSeconds();
//
//		// 다음 프레임까지 대기
//		GetOwner()->GetWorld()->Tick(ELevelTick::LEVELTICK_All, GetWorld()->GetDeltaSeconds());
//	}
//
//	// 투명도 애니메이션 종료
//	SetActorHiddenInGame(false);
//	SetActorEnableCollision(true);
//	SetActorTickEnabled(true);
//
//	UE_LOG(LogTemp, Error, TEXT("Change Opacity has taken"));
//
//	return true;	//투명도 조절이 끝나면 true 값 반환 -> 생성 애니메이션 재생
//}

void ABaseMonster::AttackStart() const
{
	WeaponCollisionBox->SetCollisionProfileName("Fist");
	WeaponCollisionBox->SetNotifyRigidBodyCollision(true);
}

void ABaseMonster::AttackEnd() const
{
	WeaponCollisionBox->SetCollisionProfileName("Fist");
	WeaponCollisionBox->SetNotifyRigidBodyCollision(false);
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

UAnimMontage* ABaseMonster::GetAtkMontage() const
{ 
	return AtkMontage; 
}

UBehaviorTree* ABaseMonster::GetBehaviorTree() const
{ 
	return BTree;
}