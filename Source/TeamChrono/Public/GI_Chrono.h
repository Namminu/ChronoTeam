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
	// About Game
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GAME", meta = (AllowPrivateAccess = "true"))
	bool isGameClear;
	// About Chrono
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CHORNO", meta = (AllowPrivateAccess = "true"))
	float ChronoInitHp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CHRONO", meta = (AllowPrivateAccess = "true"))
	float ChronoCurrentHp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CHRONO", meta = (AllowPrivateAccess = "true"))
	float Chrono_BeforeSpawnHp = 100;

public:
/// Getter	
	UFUNCTION(BlueprintCallable)
	float GetChronoMaxHp() const { return ChronoInitHp; }
	UFUNCTION(BlueprintCallable)
	float GetChronoNowHp() const { return ChronoCurrentHp; }
	UFUNCTION(BlueprintCallable)
	float GetChrono_SpawnHpRate() const { return Chrono_BeforeSpawnHp; }
	UFUNCTION(BlueprintCallable)
	bool GetGameClear() const { return isGameClear; }

/// Setter
	UFUNCTION(BlueprintCallable)
	void SetChronoNowHp(const float newFloat) { ChronoCurrentHp = newFloat; }
	UFUNCTION(BlueprintCallable)
	void SetChrono_SpawnHpRate(const float newFloat) { Chrono_BeforeSpawnHp = newFloat; }
	UFUNCTION(BlueprintCallable)
	void SetGameClear(const bool newBool) { isGameClear = newBool; }
};
