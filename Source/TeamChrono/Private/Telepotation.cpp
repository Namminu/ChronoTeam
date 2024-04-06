// Fill out your copyright notice in the Description page of Project Settings.


#include "Telepotation.h"
#include "Components/BoxComponent.h"
#include "Components/ArrowComponent.h"
#include <TeamChrono/TeamChronoCharacter.h>
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ATelepotation::ATelepotation()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Overlap Box"));
	RootComponent = collider;

	arrowTarget = CreateDefaultSubobject<UArrowComponent>(TEXT("Target Location Arrow"));
	arrowTarget->SetupAttachment(collider);
}

void ATelepotation::Teleport(AActor* actor)
{
	//Set collision actor location to arrow(target) location
	actor->SetActorRelativeLocation(arrowTarget->GetComponentLocation());
}

void ATelepotation::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if (OtherActor->ActorHasTag("PLAYER"))
	{
		FadeIn(OtherActor);
		Teleport(OtherActor);
	}
}

// Called when the game starts or when spawned
void ATelepotation::BeginPlay()
{
	Super::BeginPlay();
	
	DrawDebugDirectionalArrow(GetWorld(), collider->GetComponentLocation(), arrowTarget->GetComponentLocation(), 140.f, FColor::Blue, true, -1.f, 0, 2.f);
}

// Called every frame
void ATelepotation::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

