// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Base_BossWeapon.generated.h"

UCLASS()
class TEAMCHRONO_API ABase_BossWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABase_BossWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void SetFlashMTI(UMaterialInstanceDynamic* MTI);

	//Setup Fst Flash MTI
	void SetFstMTI(UMaterialInstanceDynamic* MTI) { Fst_MTI = MTI; }
	UMaterialInstanceDynamic* GetFstMTI() const { return Fst_MTI; }

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void DamageFlash();

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SKM", meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* WeaponSK;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "DAMAGE FLASH", meta = (AllowPrivateAccess = "true"))
	class UMaterialInstanceDynamic* Fst_MTI;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DAMAGE FLASH", meta = (AllowPrivateAccess = "true"))
	TArray<UMaterialInstanceDynamic*> MTIArray;
};
