// Copyright Epic Games, Inc. All Rights Reserved.

#include "TeamChronoGameMode.h"
#include "TeamChronoCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "MyPlayerController.h"
ATeamChronoGameMode::ATeamChronoGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	PlayerControllerClass = AMyPlayerController::StaticClass();
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
