// Fill out your copyright notice in the Description page of Project Settings.


#include "ASword.h"

// Sets default values
AASword::AASword()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	Sword = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WEAPON"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SW(TEXT("/Game/PlayerCharacter/SM_PROP_weapon_sword_dungeon_1.SM_PROP_weapon_sword_dungeon_1"));
	if (SW.Succeeded())
	{
		Sword->SetStaticMesh(SW.Object);
	}
	Sword->SetCollisionProfileName(TEXT("NoCollision"));
}

// Called when the game starts or when spawned
void AASword::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AASword::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

