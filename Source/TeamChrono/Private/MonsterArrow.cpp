// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterArrow.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/BoxComponent.h"
#include <Kismet/GameplayStatics.h>
#include <GameFramework/ProjectileMovementComponent.h>

// Sets default values
AMonsterArrow::AMonsterArrow()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CollBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Coll Box"));
	RootComponent = CollBox;

	ArrowShape = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Arrow Shape Effect"));
	ArrowShape->SetupAttachment(CollBox);

	HitEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Hit Effect"));
	HitEffect->SetupAttachment(CollBox);

	ProjectileComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Component"));
}

// Called when the game starts or when spawned
void AMonsterArrow::BeginPlay()
{
	Super::BeginPlay();
	
	HitEffect->Deactivate();

	CollBox->OnComponentBeginOverlap.AddDynamic(this, &AMonsterArrow::OnAttackOverlapBegin);
}

// Called every frame
void AMonsterArrow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMonsterArrow::OnAttackOverlapBegin(UPrimitiveComponent* const OverlappedComponent, AActor* const otherActor, 
	UPrimitiveComponent* const OtherComponent, int const OtherBodyIndex, bool const FromSweep, FHitResult const& SweepResult)
{
	if (otherActor == this || otherActor->ActorHasTag("MONSTER")) return;

	if (OtherComponent->ComponentHasTag("PLAYER"))
	{
		CallNiagaraEffect();
		UGameplayStatics::ApplyDamage(otherActor, 1, nullptr, this, DamageType);
	}

	ProjectileComponent->Deactivate();
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AMonsterArrow::ArrowDestroy, delay, false);
}

void AMonsterArrow::CallNiagaraEffect()
{
	HitEffect->Activate();
}

