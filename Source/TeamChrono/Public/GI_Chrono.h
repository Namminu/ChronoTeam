// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GI_Chrono.generated.h"

/**
 * 
 */
UCLASS()
class TEAMCHRONO_API UGI_Chrono : public UGameInstance
{
	GENERATED_BODY()
	
	virtual void Init();

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CHORNO", meta = (AllowPrivateAccess = "true"))
	float ChronoInitHp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CHRONO", meta = (AllowPrivateAccess = "true"))
	float ChronoCurrentHp;

public:
	UFUNCTION(BlueprintCallable)
	float GetChronoMaxHp() const { return ChronoInitHp; }
	UFUNCTION(BlueprintCallable)
	float GetChronoNowHp() const { return ChronoCurrentHp; }

	UFUNCTION(BlueprintCallable)
	void SetChronoNowHp(const float newFloat) { ChronoCurrentHp = newFloat; }
};
