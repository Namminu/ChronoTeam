// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MonsterSpawner.h"
#include "Magician_MonsterSpawner.generated.h"

/**
 * 
 */
UCLASS()
class TEAMCHRONO_API AMagician_MonsterSpawner : public AMonsterSpawner
{
	GENERATED_BODY()
public:
	void SpawnMonster_Implementation() override;
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MAGICIAN", meta = (AllowPrivateAccess = "true"))
	FString MagicianTag;

public:
	FString GetMagicTag() const { return MagicianTag; }
};
