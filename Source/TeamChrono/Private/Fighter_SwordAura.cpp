// Fill out your copyright notice in the Description page of Project Settings.


#include "Fighter_SwordAura.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"

// Sets default values
AFighter_SwordAura::AFighter_SwordAura()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("Root Scene"));
	RootComponent = RootScene;

	SwordAuraEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Sword Aura Effect"));
	SwordAuraEffect->SetupAttachment(RootScene);
}

// Called when the game starts or when spawned
void AFighter_SwordAura::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFighter_SwordAura::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

