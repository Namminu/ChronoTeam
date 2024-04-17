// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base_Boss.h"
#include "Boss_Fighter.generated.h"

/**
 * 
 */
UCLASS()
class TEAMCHRONO_API ABoss_Fighter : public ABase_Boss
{
	GENERATED_BODY()
	
public:
	ABoss_Fighter();

protected:
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called when Actor Destroy
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;


public:



private:



public:
///Getter


///Setter

};
