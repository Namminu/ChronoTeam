// Fill out your copyright notice in the Description page of Project Settings.


#include "Boss_TimeMaster.h"

ABoss_TimeMaster::ABoss_TimeMaster()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ABoss_TimeMaster::BeginPlay()
{
	Super::BeginPlay();

}

void ABoss_TimeMaster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABoss_TimeMaster::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}
