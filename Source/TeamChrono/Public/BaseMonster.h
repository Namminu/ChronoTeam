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

	UAnimMontage* GetAtkMontage() const;

	int MeleeAttack_Implementation() override;

	//생성 시 투명도 조절 함수
	bool Change_Opacity(float StartAlpha, float EndAlpha);

	void AttackStart() const;
	void AttackEnd() const;

	float TakeDamage(float DamageAmount,
		struct FDamageEvent const& DamageEvent, 
		AController* EventInstigator, 
		AActor* DamageCauser) override;

	//Damage Flash 함수 - 반짝임
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void DamageFlash();

	//몬스터 사망 호출 함수
	void mon_Death();

	void mon_Destroy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
private: 
///
	//비헤이비어 트리
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	UBehaviorTree* BTree;
	//공격 애니메이션 몽타주
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation, meta =(AllowPrivateAccess = "true"))
	UAnimMontage* AtkMontage;
	//생성 애니메이션 몽타주
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation, meta = (AllowPrivateAccess = "true"))
	UAnimMontage* CreateMontage;
	//사망 애니메이션 몽타주
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation, meta = (AllowPrivateAccess = "true"))
	UAnimMontage* DeathMontage;

///
	//공격 히트박스 //현재는 오른손 -> 추후 무기 셋업 후 무기 쪽으로 변경 예정
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collision, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* RightFirstCollisionBox;

///
	UFUNCTION()
	void OnAttackOverlapBegin(UPrimitiveComponent* const OverlappedComponent,
		AActor* const otherActor,
		UPrimitiveComponent* const OtherComponent,
		int const OtherBodyIndex,
		bool const FromSweep,
		FHitResult const& SweepResult);

	UFUNCTION()
	void OnAttackOverlapEnd(UPrimitiveComponent* const OverlappedComponent,
		AActor* const otherActor,
		UPrimitiveComponent* const OtherComponent,
		int const OtherBodyIndex);

///
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

	//투명도 조절 시간
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MONSTER", meta = (AllowPrivateAccess = "true"))
	float duration;

	//데미지 반짝임 반복 횟수
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DAMAGE FLASH", meta = (AllowPrivateAccess = "true"))
	float flashCount;

public:
	int GetMonSpeed() const { return monSpeed; }	
	int GetMonAtkRange() const { return monAtkRange; }	
	int GetMonCurrentHp() const { return monNowHp; } 
	int GetMonAtk() const { return monAtk; }

};
