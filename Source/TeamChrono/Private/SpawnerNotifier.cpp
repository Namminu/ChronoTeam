// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnerNotifier.h"
#include "TeamChrono/TeamChronoCharacter.h"

// Sets default values
ASpawnerNotifier::ASpawnerNotifier()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//BoxCollision Setup
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	SetRootComponent(CollisionBox);
	CollisionBox->SetRelativeScale3D(FVector(2,2,1));
	//OnOverlapEnd 이벤트 바인드
	CollisionBox->OnComponentEndOverlap.AddDynamic(this, &ASpawnerNotifier::OnOverlapEnd);
}

// Called when the game starts or when spawned
void ASpawnerNotifier::BeginPlay()
{
	Super::BeginPlay();
	 
}

// Called every frame
void ASpawnerNotifier::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpawnerNotifier::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	auto const* const Player = Cast<ATeamChronoCharacter>(OtherActor);
	if (Player && !isGetWorked)
	{
		isGetWorked = true;
		//OverlapEnd 시 spawner의 SpawnMonster() 실행
		for (AMonsterSpawner* SpawnerClass : SpawnerArray)
		{
			if (SpawnerClass)
			{
				// 특정 함수 호출
				SpawnerClass->SpawnMonster();
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("SpawnerNotifier has failed to Casting on Player"));
	}
}