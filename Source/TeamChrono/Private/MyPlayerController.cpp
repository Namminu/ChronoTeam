// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"

void AMyPlayerController::BeginPlay()
{
    Super::BeginPlay();

    // 마우스를 보이게 설정
    bShowMouseCursor = true;
}