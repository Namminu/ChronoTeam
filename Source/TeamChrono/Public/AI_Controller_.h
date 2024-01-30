// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "AI_Controller_.generated.h"

/**
 * 
 */
UCLASS()
class TEAMCHRONO_API AAI_Controller_ : public AAIController
{
	GENERATED_BODY()
	
public:
	explicit AAI_Controller_(FObjectInitializer const& ObjectInitializer);

protected:
	virtual void OnPossess(APawn* InPawn) override;

private:
	class UAISenseConfig_Sight* SightConfig;

	void SetupPerceptionSystem();

	UFUNCTION()
	void OnTargetDetected(AActor* actor, FAIStimulus const stimulus);

	//UFUNCTION()
	//void IsMonsterBorned(AActor* actor, FAIStimulus const stimulus);
};
