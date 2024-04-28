// Fill out your copyright notice in the Description page of Project Settings.


#include "Fighter_Lightning.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Boss_Fighter.h"

// Sets default values
AFighter_Lightning::AFighter_Lightning()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("Root Scene"));
	RootComponent = RootScene;

	LightningEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Lightning Effect"));
	LightningEffect->SetupAttachment(RootScene);
}

// Called when the game starts or when spawned
void AFighter_Lightning::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AFighter_Lightning::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

