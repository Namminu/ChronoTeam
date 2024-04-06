// Fill out your copyright notice in the Description page of Project Settings.


#include "Magician_MagicBall.h"
#include <Kismet/GameplayStatics.h>
#include "Components/SphereComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include <BaseMonster.h>
#include "Components/CapsuleComponent.h"

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

	bisPlayerhit = false;

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
	if (otherActor->ActorHasTag("PLAYER"))
	{
		UE_LOG(LogTemp, Warning, TEXT("First, Overlap to Player"));

		if (bisPlayerhit) return;

		//if (OtherComponent->ComponentHasTag("SWORD"))
		//{
		//	UE_LOG(LogTemp, Warning, TEXT("Sword box overlap"));
		//	Re_Elasticity();
		//	Re_Elasticity();
		//}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("MagicBall : hits Player"));
			UGameplayStatics::ApplyDamage(otherActor, damageAmount, nullptr, this, DamageType);
			HitNBurn();
		}
	}
	else
	{
		if (otherActor == this) return;
		if (otherActor->ActorHasTag("MONSTER"))
		{
			if (!bisPlayerhit) return;	//플레이어가 투사체 hit 전	
			else if (bisPlayerhit)		//플레이어가 투사체 hit 후
			{
				ABaseMonster* monster = Cast<ABaseMonster>(otherActor);
				if (UCapsuleComponent* CapsuleComponent = Cast<UCapsuleComponent>(OtherComponent))
				{
					if (CapsuleComponent == monster->GetCapsuleComponent())
					{
						UGameplayStatics::ApplyDamage(otherActor, damageAmount, nullptr, this, DamageType);
						HitNBurn();
					}
				}
				else
				{
					UE_LOG(LogTemp, Error, TEXT("Failed : ApplyDamage to Monster"));
				}
			}
		}
		else Destroy();
	}

//
	//if (otherActor->ActorHasTag("PLAYER"))
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("First, Overlap to Player"));
	//	if (OtherComponent->ComponentHasTag("SWORD"))
	//	{
	//		UE_LOG(LogTemp, Warning, TEXT("Sword box overlap"));
	//		Re_Elasticity();
	//	}
	//	else
	//	{
	//		UE_LOG(LogTemp, Warning, TEXT("MagicBall : hits Player"));
	//		UGameplayStatics::ApplyDamage(otherActor, damageAmount, nullptr, this, DamageType);
	//		Destroy();
	//	}
	//}
	//else
	//{
	//	if (otherActor == this || otherActor->ActorHasTag("MONSTER")) return;
	//	else
	//	{
	//		UE_LOG(LogTemp, Warning, TEXT("Magician's MagicBall overlap to otherActor"));
	//	}
	//	Destroy();
	//}
}

void AMagician_MagicBall::OnProjectileOverlapEnd(UPrimitiveComponent* const OverlappedComponent,
	AActor* const otherActor, UPrimitiveComponent* const OtherComponent, int const OtherBodyIndex)
{
}

float AMagician_MagicBall::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent,
	AController* EventInstigator, AActor* DamageCauser)
{
	Re_Elasticity();
	Re_Elasticity();
	return 0.0f;
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
	bisPlayerhit = true;
	damageAmount = re_DamageAmount;
	FVector playerForward = player->GetActorForwardVector();
	//playerForward.Normalize();
	ProjectileComponent->Velocity = playerForward * (ProjectileComponent->InitialSpeed);
	SetMagicSpeed(ProjectileComponent->InitialSpeed * re_Speed);
	UE_LOG(LogTemp, Warning, TEXT("MagicBall : Hitted by Player so ReElasticity"));
}