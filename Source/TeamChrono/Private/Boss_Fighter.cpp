// Fill out your copyright notice in the Description page of Project Settings.


#include "Boss_Fighter.h"

ABoss_Fighter::ABoss_Fighter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	sk_Helm = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Helmet Mesh"));
	sk_Helm->SetupAttachment(GetMesh());
	sk_Helm->SetLeaderPoseComponent(GetMesh());

	sk_Shoulders = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Shoulders Mesh"));
	sk_Shoulders->SetupAttachment(GetMesh());
	sk_Shoulders->SetLeaderPoseComponent(GetMesh());

	sk_Chest = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Chest Mesh"));
	sk_Chest->SetupAttachment(GetMesh());
	sk_Chest->SetLeaderPoseComponent(GetMesh());

	sk_Belt = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Belt Mesh"));
	sk_Belt->SetupAttachment(GetMesh());
	sk_Belt->SetLeaderPoseComponent(GetMesh());

	sk_Legs = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Legs Mesh"));
	sk_Legs->SetupAttachment(GetMesh());
	sk_Legs->SetLeaderPoseComponent(GetMesh());

	sk_Cape = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Cape Mesh"));
	sk_Cape->SetupAttachment(GetMesh());
	sk_Cape->SetLeaderPoseComponent(GetMesh());

	sk_Hands = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Hands Mesh"));
	sk_Hands->SetupAttachment(GetMesh());
	sk_Hands->SetLeaderPoseComponent(GetMesh());

	sk_Bracers = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Bracers Mesh"));
	sk_Bracers->SetupAttachment(GetMesh());
	sk_Bracers->SetLeaderPoseComponent(GetMesh());

	sk_Boots = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Boots Mesh"));
	sk_Boots->SetupAttachment(GetMesh());
	sk_Boots->SetLeaderPoseComponent(GetMesh());

	
}

void ABoss_Fighter::BeginPlay()
{
	Super::BeginPlay();

}

void ABoss_Fighter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

int ABoss_Fighter::MeleeAttack_Implementation()
{
	return 0;
}

void ABoss_Fighter::Boss_Death_Implementation()
{
}

float ABoss_Fighter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	return 0.0f;
}

void ABoss_Fighter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

}