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

	PinMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Pin Mesh"));
	PinMesh->SetupAttachment(RootScene);

	ImplusePoint = CreateDefaultSubobject<USceneComponent>(TEXT("Impulse Point"));
	ImplusePoint->SetupAttachment(RootScene);
}

// Called when the game starts or when spawned
void AChrono_Weapon_ClockPin::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AChrono_Weapon_ClockPin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
