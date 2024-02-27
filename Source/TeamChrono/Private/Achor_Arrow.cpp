// Fill out your copyright notice in the Description page of Project Settings.


#include "Achor_Arrow.h"
#include "BaseMonster.h"
#include "Components/CapsuleComponent.h"
#include <Kismet/GameplayStatics.h>
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"

// Sets default values
AAchor_Arrow::AAchor_Arrow()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//RootComponent Setup
	Root= CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	RootComponent = Root;

	//Weapon Setup
	Arrow = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Arrow"));
	Arrow->SetupAttachment(Root);

	//CollisionBox Setup
	CollisionBox = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collision Box"));
	CollisionBox->SetupAttachment(Arrow);

	//Projectile Setup
	ProjectileComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Component"));

	//Niagara Effect
	NiagaraEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Niagara Component"));
	NiagaraEffect->SetupAttachment(Root);
}

void AAchor_Arrow::OnAttackOverlapBegin(UPrimitiveComponent* const OverlappedComponent, 
	AActor* const otherActor,
	UPrimitiveComponent* const OtherComponent,
	int const OtherBodyIndex, bool const FromSweep, 
	FHitResult const& SweepResult)
{
	if (otherActor == this) return;

	CallNiagaraEffect();	//Niaraga Effect when Arrow hit Something / Without this

	if (otherActor->ActorHasTag("PLAYER"))
	{
		UE_LOG(LogTemp, Warning, TEXT("Arrow : hits Player"));

		UGameplayStatics::ApplyDamage(otherActor, damageAmount, nullptr, this, DamageType);
	}
	
	UE_LOG(LogTemp, Warning, TEXT("Arrow : Destory by overlap"));
	ProjectileComponent->Deactivate();
	//Destroy();	//destory when hits actor
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AAchor_Arrow::arrowDestroy, delay, false);
}

void AAchor_Arrow::OnAttackOverlapEnd(UPrimitiveComponent* const OverlappedComponent,
	AActor* const otherActor, UPrimitiveComponent* const OtherComponent, int const OtherBodyIndex)
{
}

void AAchor_Arrow::CallNiagaraEffect()
{
	NiagaraEffect->Activate();
}

void AAchor_Arrow::arrowDestroy()
{
	Destroy();
}

//void AAchor_Arrow::DestoryByDistance_Implementation(float distance)
//{
//	//Every Tick for Current Arrow Location
//	CurrentPosition = GetActorLocation();
//
//	//if ((CurrentPosition - StartPosition).X > distance)
//	//{
//	//	UE_LOG(LogTemp, Error, TEXT("Arrow Destory Time"));
//	//	Destroy();
//	//}
//
//
//}

// Called when the game starts or when spawned
void AAchor_Arrow::BeginPlay()
{
	Super::BeginPlay();
	
	//Begin With Deactivate Niagara Effect
	NiagaraEffect->Deactivate();

	damageAmount = 1;

	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AAchor_Arrow::OnAttackOverlapBegin);
	CollisionBox->OnComponentEndOverlap.AddDynamic(this, &AAchor_Arrow::OnAttackOverlapEnd);
}

// Called every frame
void AAchor_Arrow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//DestoryByDistance_Implementation(arrowDistance);
}

