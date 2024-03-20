// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Monster_Weapon.generated.h"

UCLASS()
class TEAMCHRONO_API AMonster_Weapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMonster_Weapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

///
	//Damage Flash �Լ� - ��¦��
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void DamageFlash();

	//Flash MTI ���� �Լ�
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void SetFlashMTI();

	//���� �� ���� ���� �Լ�
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void Change_Opacity(float StartAlpha, float EndAlpha);

///
	void Wp_Destroy();
	void Wp_Death();

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "WEAPON", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Weapon;

public:
	/// 
	UStaticMeshComponent* GetWeaponMesh() { return Weapon; }
};
