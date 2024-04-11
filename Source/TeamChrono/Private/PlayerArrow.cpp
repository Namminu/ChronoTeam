// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerArrow.h"

// Sets default values
APlayerArrow::APlayerArrow()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	Bow = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WEAPON"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SW(TEXT("/Script/Engine.StaticMesh'/Game/PlayerCharacter/waepon/bow/non_arrow/bow_non_arrow.bow_non_arrow'"));
	if (SW.Succeeded())
	{
		Bow->SetStaticMesh(SW.Object);
	}
	Bow->SetCollisionProfileName(TEXT("NoCollision"));
}

// Called when the game starts or when spawned
void APlayerArrow::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerArrow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

