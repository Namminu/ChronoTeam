// Fill out your copyright notice in the Description page of Project Settings.


#include "Achor_Arrow.h"
#include "BaseMonster.h"

// Sets default values
AAchor_Arrow::AAchor_Arrow()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Weapon Setup
	Arrow = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Arrow"));
	SetRootComponent(Arrow);
}

void AAchor_Arrow::LaunchForward_Implementation(float distance)
{

}

// Called when the game starts or when spawned
void AAchor_Arrow::BeginPlay()
{
	Super::BeginPlay();
	
	//Launch to Forward When Arrow Spawn
	if (ABaseMonster* mon = Cast<ABaseMonster>(GetOwner()))
	{
		LaunchForward(mon->GetArrowDistance());
	}
}

// Called every frame
void AAchor_Arrow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

