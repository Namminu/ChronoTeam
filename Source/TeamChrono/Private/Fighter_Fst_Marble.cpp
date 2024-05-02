// Fill out your copyright notice in the Description page of Project Settings.


#include "Fighter_Fst_Marble.h"
#include "Components/SphereComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"

// Sets default values
AFighter_Fst_Marble::AFighter_Fst_Marble()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = RootScene;

	RootSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	RootSphere->SetupAttachment(RootScene);

	Fst_Effect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Fst Effect"));
	Fst_Effect->SetupAttachment(RootScene);
}

// Called when the game starts or when spawned
void AFighter_Fst_Marble::BeginPlay()
{
	Super::BeginPlay();
	
	RootSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}

// Called every frame
void AFighter_Fst_Marble::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

