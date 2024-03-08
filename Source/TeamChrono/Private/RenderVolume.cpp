// Fill out your copyright notice in the Description page of Project Settings.


#include "RenderVolume.h"
#include "Components/BoxComponent.h"

// Sets default values
ARenderVolume::ARenderVolume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Rendering Box"));
	RootComponent = collider;
}

// Called when the game starts or when spawned
void ARenderVolume::BeginPlay()
{
	Super::BeginPlay();
	
	collider->GetOverlappingActors(OverlappingActors);

	for (AActor* Actor : OverlappingActors)
	{
		Actor->SetActorHiddenInGame(true);
	}

	UE_LOG(LogTemp, Error, TEXT("Rendering Box had %d of Actors"), OverlappingActors.Num());
}

void ARenderVolume::NotifyActorBeginOverlap(AActor* OtherActor)
{
	collider->GetOverlappingActors(OverlappingActors);
	
	if(OtherActor->ActorHasTag("PLAYER"))
	{
		OverlappingActors.Remove(OtherActor);

		for (AActor* Actor : OverlappingActors)
		{
			Actor->SetActorHiddenInGame(false);
		}
	}
}

void ARenderVolume::NotifyActorEndOverlap(AActor* OtherActor)
{
	if (OtherActor->ActorHasTag("PLAYER"))
	{
		for (AActor* Actor : OverlappingActors)
		{
			Actor->SetActorHiddenInGame(true);
		}
	}
}

// Called every frame
void ARenderVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

