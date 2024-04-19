// Fill out your copyright notice in the Description page of Project Settings.


#include "Base_BossWeapon.h"

// Sets default values
ABase_BossWeapon::ABase_BossWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WeaponSK = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon Sk"));
	RootComponent = WeaponSK;
}

// Called when the game starts or when spawned
void ABase_BossWeapon::BeginPlay()
{
	Super::BeginPlay();
	
	SetFstMTI(WeaponSK->CreateDynamicMaterialInstance(0));
	SetFlashMTI(GetFstMTI());
}

void ABase_BossWeapon::SetFlashMTI(UMaterialInstanceDynamic* MTI)
{
	if (MTI)
	{
		MTIArray.Add(MTI);
	}
}

// Called every frame
void ABase_BossWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

