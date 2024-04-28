// Fill out your copyright notice in the Description page of Project Settings.


#include "Fighter_Tornado.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"

// Sets default values
AFighter_Tornado::AFighter_Tornado()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("Root Scene"));
	RootComponent = RootScene;

	TornadoEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Attack Effect"));
	TornadoEffect->SetupAttachment(RootScene);
}

// Called when the game starts or when spawned
void AFighter_Tornado::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFighter_Tornado::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

