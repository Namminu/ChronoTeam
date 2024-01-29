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
	//OnOverlapEnd �̺�Ʈ ���ε�
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
		//OverlapEnd �� spawner�� SpawnMonster() ����
		for (AMonsterSpawner* SpawnerClass : SpawnerArray)
		{
			if (SpawnerClass)
			{
				// Ư�� �Լ� ȣ��
				SpawnerClass->SpawnMonster();
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("SpawnerNotifier has failed to Casting on Player"));
	}
}