// Fill out your copyright notice in the Description page of Project Settings.


#include "Achor_Arrow.h"
#include "BaseMonster.h"

// Sets default values
AAchor_Arrow::AAchor_Arrow()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//RootComponent Setup
	Root= CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	RootComponent = Root;

	//Weapon Setup
	Arrow = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Arrow"));
	Arrow->SetupAttachment(Root);

	//Projectile Setup
	ProjectileComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Component"));
}

void AAchor_Arrow::DestoryByDistance_Implementation(float distance)
{
	//Every Tick for Current Arrow Location
	CurrentPosition = GetActorLocation();

	//if ((CurrentPosition - StartPosition).X > distance)
	//{
	//	UE_LOG(LogTemp, Error, TEXT("Arrow Destory Time"));
	//	Destroy();
	//}

	UE_LOG(LogTemp, Warning, TEXT("%f"), arrowDistance);
}

// Called when the game starts or when spawned
void AAchor_Arrow::BeginPlay()
{
	Super::BeginPlay();
	
	//Set Actor begin vector
	StartPosition = GetActorLocation();

	//Get Arrow Distance by BaseMonster
	if (ABaseMonster* mon = Cast<ABaseMonster>(GetOwner()))
	{
		arrowDistance = mon->GetArrowDistance();
	}

}

// Called every frame
void AAchor_Arrow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DestoryByDistance_Implementation(arrowDistance);
}

