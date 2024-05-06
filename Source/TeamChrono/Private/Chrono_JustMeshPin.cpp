// Fill out your copyright notice in the Description page of Project Settings.


#include "Chrono_JustMeshPin.h"

// Sets default values
AChrono_JustMeshPin::AChrono_JustMeshPin()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PinMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Root Pin Mesh"));
	RootComponent = PinMesh;
}

// Called when the game starts or when spawned
void AChrono_JustMeshPin::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AChrono_JustMeshPin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

