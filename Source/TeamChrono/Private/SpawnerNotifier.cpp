// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnerNotifier.h"
#include "Components/BoxComponent.h"

// Sets default values
ASpawnerNotifier::ASpawnerNotifier()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("ProjectileMovementComponent"));
	//CollisionBox->SetUpdatedComponent();

	//OnOverlapEnd �̺�Ʈ ���ε�
	//CollisionBox->OnComponentEndOverlap.AddDynamic(this, &ASpawnerNotifier::OnOverlapEnd);
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
	//OverlapEnd �� spawner�� SpawnMonster() ����
}


