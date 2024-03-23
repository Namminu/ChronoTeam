// Fill out your copyright notice in the Description page of Project Settings.


#include "Magician_MagicBall.h"
#include <Kismet/GameplayStatics.h>
#include "Components/SphereComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"

// Sets default values
AMagician_MagicBall::AMagician_MagicBall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Set Sphere Component
	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere_Root"));
	RootComponent = Sphere;
	//Set Niagara Effect Component
	NiagaraEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Niagara_Effect"));
	NiagaraEffect->SetupAttachment(Sphere);
	//Set Projectile
	ProjectileComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Component"));

}

// Called when the game starts or when spawned
void AMagician_MagicBall::BeginPlay()
{
	Super::BeginPlay();

	//Add Dynamic Function
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AMagician_MagicBall::OnProjectileOverlapBegin);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &AMagician_MagicBall::OnProjectileOverlapEnd);

	//Cast to Player
	player = Cast<ATeamChronoCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	if (player == nullptr) UE_LOG(LogTemp, Error, TEXT("Magicball has Cast failed to Player"));

}

// Called every frame
void AMagician_MagicBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bisPlayerhit)
	{
		//Projectile Always Chase Player when player does not hit projectile
		ChasePlayer();
	}

}

void AMagician_MagicBall::OnProjectileOverlapBegin(UPrimitiveComponent* const OverlappedComponent,
	AActor* const otherActor, UPrimitiveComponent* const OtherComponent, 
	int const OtherBodyIndex, bool const FromSweep,
	FHitResult const& SweepResult)
{
	//플레이어의 검 - 공격 타이밍에 부딪힐 경우
	if (otherActor->ActorHasTag("SWORD"))
	{
		Re_Elasticity();
	}
	else
	{
		//자기 자신일 경우 or 몬스터에 부딪힐 경우
		if (otherActor == this || otherActor->ActorHasTag("MONSTER")) return;
		//플레이어에 부딪힐 경우
		if (otherActor->ActorHasTag("PLAYER"))
		{
			UE_LOG(LogTemp, Warning, TEXT("MagicBall : hits Player"));
			UGameplayStatics::ApplyDamage(otherActor, damageAmount, nullptr, this, DamageType);
		}
		//벽 등 다른 액터에 부딪힐 경우
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Magician's MagicBall overlap to otherActor"));

		}
		Destroy();
	}
}

void AMagician_MagicBall::OnProjectileOverlapEnd(UPrimitiveComponent* const OverlappedComponent,
	AActor* const otherActor, UPrimitiveComponent* const OtherComponent, int const OtherBodyIndex)
{
}

void AMagician_MagicBall::ChasePlayer()
{
	FVector playerLocation = player->GetActorLocation();
	FVector targetDirection = playerLocation - this->GetActorLocation();
	targetDirection.Normalize();

	ProjectileComponent->Velocity = targetDirection * (ProjectileComponent->InitialSpeed);
}

void AMagician_MagicBall::Re_Elasticity()
{
	UE_LOG(LogTemp, Warning, TEXT("MagicBall : Hitted by Player so ReElasticity"));
	FRotator newRotator = player->GetActorRotation();


}