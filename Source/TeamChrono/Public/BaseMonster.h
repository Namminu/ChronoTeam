// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BehaviorTree.h"
#include "GameFramework/Character.h"
#include "CombatInterface.h"
#include "Animation/AnimMontage.h"
#include "BaseMonster.generated.h"

UCLASS()
class TEAMCHRONO_API ABaseMonster : public ACharacter, public ICombatInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseMonster();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UBehaviorTree* GetBehaviorTree() const;

	UAnimMontage* GetMontage() const;

	int MeleeAttack_Implementation() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	UBehaviorTree* BTree;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation, meta =(AllowPrivateAccess = "true"))
	UAnimMontage* Montage;

	//몬스터 최대 체력
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MONSTER", meta = (AllowPrivateAccess = "true"))
	int monMaxHp;
	//몬스터 현재 체력
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MONSTER", meta = (AllowPrivateAccess = "true"))
	int monNowHp;
	//몬스터 이동 속도
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MONSTER", meta = (AllowPrivateAccess = "true"))
	int monSpeed;	
	//몬스터 공격 범위
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MONSTER", meta = (AllowPrivateAccess = "true"))
	int monAtkRange;
	//몬스터 공격력
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MONSTER", meta = (AllowPrivateAccess = "true"))
	int monAtk;

public:
	int GetMonSpeed() const { return monSpeed; }	
	int GetMonAtkRange() const { return monAtkRange; }	
	int GetMonCurrentHp() const { return monNowHp; } 
	int GetMonAtk() const { return monAtk; }
};
