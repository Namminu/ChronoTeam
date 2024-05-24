// Fill out your copyright notice in the Description page of Project Settings.


#include "NotifierDoor.h"
#include "Components/BoxComponent.h"
#include "MonsterSpawner.h"
#include "DoorNextDoor.h"
#include <TeamChrono/TeamChronoCharacter.h>
#include <Kismet/GameplayStatics.h>

// Sets default values
ANotifierDoor::ANotifierDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("Root Scene"));
	RootComponent = RootScene;

	BoxColl = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Coll"));
	BoxColl->SetupAttachment(RootScene);
}

// Called when the game starts or when spawned
void ANotifierDoor::BeginPlay()
{
	Super::BeginPlay();

	isGetWorked = false;

	BoxColl->OnComponentEndOverlap.AddDynamic(this, &ANotifierDoor::OnOverlapEnd);
}

// Called every frame
void ANotifierDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (isGetWorked)
	{
		if (SpawnerArray.Num() == 0)
		{
			SetOpenDoor();
			SetActorTickEnabled(false);
		}

		//for (AMonsterSpawner* Spawner : SpawnerArray)
		//{
		//	if (Spawner->GetAllMonsterDie())
		//	{

		//	}
		//}
	}
}

void ANotifierDoor::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, 
	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->ActorHasTag("PLAYER"))
	{
		if (!isGetWorked)
		{
			SetPlayerESkillLocation();

			for (AMonsterSpawner* Spawner : SpawnerArray)
			{
				Spawner->SpawnMonster();
			}
			isGetWorked = true;
			SetCloseDoor();
		}
		Temp_Initialize();
	}
}

