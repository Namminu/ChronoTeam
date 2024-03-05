// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelTransferVolume.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"

// Sets default values
ALevelTransferVolume::ALevelTransferVolume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TransferVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("Transfer Volume"));
	SetRootComponent(TransferVolume);
	//TransferVolume->SetCollisionProfileName(TEXT("OverlapOnlyPawn"));
}

void ALevelTransferVolume::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if (OtherActor->ActorHasTag("PLAYER"))
	{
		UGameplayStatics::OpenLevel(this, TransferLevelName);
	}
}

// Called when the game starts or when spawned
void ALevelTransferVolume::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALevelTransferVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

