// Fill out your copyright notice in the Description page of Project Settings.


#include "Chrono_Weapon_ClockPin.h"
#include "Components/BoxComponent.h"

// Sets default values
AChrono_Weapon_ClockPin::AChrono_Weapon_ClockPin()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("Root Scene"));
	RootComponent = RootScene;

	BoxColl = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Coll"));
	BoxColl->SetupAttachment(RootScene);

	PinMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Pin Mesh"));
	PinMesh->SetupAttachment(BoxColl);

	ImplusePoint = CreateDefaultSubobject<USceneComponent>(TEXT("Impulse Point"));
	ImplusePoint->SetupAttachment(BoxColl);

	ProjectileComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Component"));
}

// Called when the game starts or when spawned
void AChrono_Weapon_ClockPin::BeginPlay()
{
	Super::BeginPlay();
	
	// For Not Launch Begin
	ProjectileComponent->InitialSpeed = 0.f;
	ProjectileComponent->MaxSpeed = 0.f;
}

// Called every frame
void AChrono_Weapon_ClockPin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AChrono_Weapon_ClockPin::LaunchPin_Implementation(float Speed)
{
	ProjectileComponent->InitialSpeed = Speed;
	ProjectileComponent->MaxSpeed = Speed + 100;

	ProjectileComponent->InitialSpeed = Speed;
	ProjectileComponent->MaxSpeed = Speed + 100;
}
