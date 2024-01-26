// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CombatInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCombatInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TEAMCHRONO_API ICombatInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	//공격 모션 override
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Combat")
	int MeleeAttack();

	//생성 모션 override
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Combat")
	int Creating();

	//포효 모션 override
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Combat")
	int Shouting();
};
