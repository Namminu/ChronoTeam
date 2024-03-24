// Fill out your copyright notice in the Description page of Project Settings.


#include "Magician_BigAttack.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/CapsuleComponent.h"
#include "Components/BoxComponent.h"
#include <Kismet/GameplayStatics.h>
#include <TeamChrono/TeamChronoCharacter.h>

// Sets default values
AMagician_BigAttack::AMagician_BigAttack()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//RootComponent Setup
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	RootComponent = Root;

	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Base Capsule"));
	Capsule->SetupAttachment(Root);

	FloorEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Floor Effect"));
	FloorEffect->SetupAttachment(GetCapsule());

	SwordHitBox1 = CreateDefaultSubobject<UBoxComponent>(TEXT("Sword Hit Box1"));
	SwordHitBox1->SetupAttachment(GetCapsule());
	SwordEffect1 = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Sword Effect1"));
	SwordEffect1->SetupAttachment(SwordHitBox1);

	SwordHitBox2 = CreateDefaultSubobject<UBoxComponent>(TEXT("Sword Hit Box2"));
	SwordHitBox2->SetupAttachment(GetCapsule());
	SwordEffect2 = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Sword Effect2"));
	SwordEffect2->SetupAttachment(SwordHitBox2);

	SwordHitBox3 = CreateDefaultSubobject<UBoxComponent>(TEXT("Sword Hit Box3"));
	SwordHitBox3->SetupAttachment(GetCapsule());
	SwordEffect3 = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Sword Effect3"));
	SwordEffect3->SetupAttachment(SwordHitBox3);

	SwordHitBox4 = CreateDefaultSubobject<UBoxComponent>(TEXT("Sword Hit Box4"));
	SwordHitBox4->SetupAttachment(GetCapsule());
	SwordEffect4 = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Sword Effect4"));
	SwordEffect4->SetupAttachment(SwordHitBox4);

	SwordHitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Sword Hit Box"));
	SwordHitBox->SetupAttachment(GetCapsule());
	SwordEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Sword Effect"));
	SwordEffect->SetupAttachment(SwordHitBox);

	HitEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Hit Effect"));
	HitEffect->SetupAttachment(GetCapsule());

	//Set Array
	HitBoxes.Add(SwordHitBox4);
	HitBoxes.Add(SwordHitBox1);
	HitBoxes.Add(SwordHitBox3);
	HitBoxes.Add(SwordHitBox2);
	HitBoxes.Add(SwordHitBox);
}

// Called when the game starts or when spawned
void AMagician_BigAttack::BeginPlay()
{
	Super::BeginPlay();

	damageAmount = 2;

	SwordEffect1->Deactivate();
	SwordEffect2->Deactivate();
	SwordEffect3->Deactivate();
	SwordEffect4->Deactivate();
	SwordEffect->Deactivate();
	HitEffect->Deactivate();

	SwordHitBox->OnComponentBeginOverlap.AddDynamic(this, &AMagician_BigAttack::OnAttackOverlapBegin);
	SwordHitBox->OnComponentEndOverlap.AddDynamic(this, &AMagician_BigAttack::OnAttackOverlapEnd);
}

// Called every frame
void AMagician_BigAttack::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMagician_BigAttack::MakeSword_Implementation()
{

}

void AMagician_BigAttack::ActivateEffect(UBoxComponent* hitbox, UNiagaraComponent* Sword)
{
	hitbox->SetNotifyRigidBodyCollision(true);
	hitbox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Sword->Activate();
}

void AMagician_BigAttack::OnAttackOverlapBegin(UPrimitiveComponent* const OverlappedComponent,
	AActor* const otherActor, UPrimitiveComponent* const OtherComponent, 
	int const OtherBodyIndex, bool const FromSweep, FHitResult const& SweepResult)
{
	if (otherActor == this) return;
	if (otherActor->ActorHasTag("MONSTER")) return;

	if (otherActor->ActorHasTag("PLAYER"))
	{
		UGameplayStatics::ApplyDamage(otherActor, damageAmount, nullptr, this, DamageType);

		FTimerHandle TimerHandle;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AMagician_BigAttack::SelfDestroy, delay, false);
	}
}

void AMagician_BigAttack::OnAttackOverlapEnd(UPrimitiveComponent* const OverlappedComponent,
	AActor* const otherActor, UPrimitiveComponent* const OtherComponent, int const OtherBodyIndex)
{
}

void AMagician_BigAttack::SelfDestroy()
{
	Destroy();
}