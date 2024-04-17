// Fill out your copyright notice in the Description page of Project Settings.


#include "Boss_Fighter.h"

ABoss_Fighter::ABoss_Fighter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ABoss_Fighter::BeginPlay()
{
	Super::BeginPlay();


}

void ABoss_Fighter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

void ABoss_Fighter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

}
