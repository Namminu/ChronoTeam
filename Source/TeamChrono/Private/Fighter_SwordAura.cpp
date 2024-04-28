// Fill out your copyright notice in the Description page of Project Settings.


#include "Fighter_SwordAura.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/BoxComponent.h"
#include "TimerManager.h"
#include <Kismet/GameplayStatics.h>
#include <TeamChrono/TeamChronoCharacter.h>

// Sets default values
AFighter_SwordAura::AFighter_SwordAura()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("Root Scene"));
	RootComponent = RootScene;

	BoxColl = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Coll"));
	BoxColl->SetupAttachment(RootScene);

	SwordAuraEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Sword Aura Effect"));
	SwordAuraEffect->SetupAttachment(RootScene);
}

// Called when the game starts or when spawned
void AFighter_SwordAura::BeginPlay()
{
	Super::BeginPlay();

	BoxColl->OnComponentBeginOverlap.AddDynamic(this, &AFighter_SwordAura::OnBoxOverlapBegin);
	BoxColl->OnComponentEndOverlap.AddDynamic(this, &AFighter_SwordAura::OnBoxOverlapEnd);
}

// Called every frame
void AFighter_SwordAura::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFighter_SwordAura::OnBoxOverlapBegin(UPrimitiveComponent* const OverlappedComponent, AActor* const otherActor, UPrimitiveComponent* const OtherComponent, int const OtherBodyIndex, bool const FromSweep, FHitResult const& SweepResult)
{
	if (otherActor->ActorHasTag("PLAYER"))
	{
		player = Cast<ATeamChronoCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		ApplyDamageToPlayer();
		SetDamageTimer();
	}
}

void AFighter_SwordAura::OnBoxOverlapEnd(UPrimitiveComponent* const OverlappedComponent, AActor* const otherActor, UPrimitiveComponent* const OtherComponent, int const OtherBodyIndex)
{
	if (otherActor->ActorHasTag("PLAYER"))
	{
		SetClearTimer();
	}
}

void AFighter_SwordAura::SetDamageTimer()
{
	GetWorld()->GetTimerManager().SetTimer(DamageTimer, this, &AFighter_SwordAura::ApplyDamageToPlayer, 1.f, true);
}

void AFighter_SwordAura::SetClearTimer()
{
	GetWorld()->GetTimerManager().ClearTimer(DamageTimer);
}

