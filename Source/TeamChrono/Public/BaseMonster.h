// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BehaviorTree.h"
#include "GameFramework/Character.h"
#include "CombatInterface.h"
#include "Animation/AnimMontage.h"
//#include "Monster_Weapon.h"
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

	UAnimMontage* GetCreateMontage() const;

	UAnimMontage* GetDeathMontage() const;

	int MeleeAttack_Implementation() override;

	//기본 공격 함수
	void AttackStart() const;
	void AttackEnd() const;

	//아처 전용 - 화살 발사 함수
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void FireArrow();

	float TakeDamage(float DamageAmount,
		struct FDamageEvent const& DamageEvent, 
		AController* EventInstigator, 
		AActor* DamageCauser) override;

	//Damage Flash 함수 - 반짝임
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void DamageFlash();

	//생성 시 투명도 조절 함수
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void Change_Opacity(float StartAlpha, float EndAlpha);

	//무기 장착 호출 함수
	UFUNCTION(BlueprintCallable)
	void AttachWeapon(TSubclassOf<AMonster_Weapon> Weapon, FName socketName);

	//나이아가라 이펙트 호출 함수
	UFUNCTION(BlueprintCallable)
	void CallNiagaraEffect(UNiagaraComponent* NiaEffect);

	//몬스터 사망 호출 함수
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void mon_Death();

	UFUNCTION(BlueprintCallable)
	virtual void mon_Destroy();

	//Create Dynamic Material Instance Function
	UFUNCTION(BlueprintCallable)
	virtual void CreateMTI();

	void PlayMontage(UAnimMontage* Montage);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void TempAttack();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void FocusToPlayer();

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
	//Fst Material Instance Date
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DAMAGE FLASH", meta = (AllowPrivateAccess = "true"))
	UMaterialInstanceDynamic* Fst_MTI;

	//Snd Material Instance Data
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DAMAGE FLASH", meta = (AllowPrivateAccess = "true"))
	UMaterialInstanceDynamic* Snd_MTI;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DAMAGE FLASH", meta = (AllowPrivateAccess = "true"))
	TArray<UMaterialInstanceDynamic*> MTIArray;
///
	////공격 히트박스
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Collision, meta = (AllowPrivateAccess = "true"))
	//class UBoxComponent* WeaponCollisionBox;
	//무기
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WEAPON", meta = (AllowPrivateAccess = "true"))
	class AMonster_Weapon* WeaponInstance;
	//공격범위 히트박스
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Collision, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* AttackRangeBox;

///
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "EFFECT", meta = (AllowPrivateAccess = "true"))
	class UNiagaraComponent* NiagaraAttackEffect;

///
	UFUNCTION()
	virtual void OnAttackOverlapBegin(UPrimitiveComponent* const OverlappedComponent,
		AActor* const otherActor,
		UPrimitiveComponent* const OtherComponent,
		int const OtherBodyIndex,
		bool const FromSweep,
		FHitResult const& SweepResult);

	UFUNCTION()
	virtual void OnAttackOverlapEnd(UPrimitiveComponent* const OverlappedComponent,
		AActor* const otherActor,
		UPrimitiveComponent* const OtherComponent,
		int const OtherBodyIndex);

	UFUNCTION()
	virtual void OnRangeOverlapBegin(UPrimitiveComponent* const OverlappedComponent,
		AActor* const otherActor,
		UPrimitiveComponent* const OtherComponent,
		int const OtherBodyIndex,
		bool const FromSweep,
		FHitResult const& SweepResult);

	UFUNCTION()
	virtual void OnRangeOverlapEnd(UPrimitiveComponent* const OverlappedComponent,
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
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MONSTER", meta = (AllowPrivateAccess = "true"))
	int monAtk;

	////아처 몬스터 화살 거리
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MONSTER_ACHOR", meta = (AllowPrivateAccess = "true"))
	//float arrow_Distance;

	//투명도 조절 시간
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MONSTER", meta = (AllowPrivateAccess = "true"))
	float duration;

	//데미지 반짝임 반복 횟수
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DAMAGE FLASH", meta = (AllowPrivateAccess = "true"))
	float flashCount;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UDamageType> DamageType;

	//공격 범위 float
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ATTACK RANGE", meta = (AllowPrivateAccess = "true"))
	float AttakRange;

	//BlackBoard Key Name
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ATTACK RANGE", meta = (AllowPrivateAccess = "true"))
	FName AttackRangeKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MONSTER BORN", meta = (AllowPrivateAccess = "true"))
	bool isMonsterBorn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool isMonsterLive;

public:
/// Property Getter
	int GetMonSpeed() const { return monSpeed; }	
	int GetMonAtkRange() const { return monAtkRange; }	
	int GetMonCurrentHp() const { return monNowHp; } 
	int GetMonMaxHp() const { return monMaxHp; }
	int GetMonAtk() const { return monAtk; }
	bool GetIsBorn() const { return isMonsterBorn; }
	bool GetMonsterLive() const { return isMonsterLive; }

/// Component Getter
	UNiagaraComponent* GetAttackEffect() const { return NiagaraAttackEffect; }
	//UBoxComponent* GetWeaponColl() const { return WeaponCollisionBox; }
	USphereComponent* GetAttackRangeColl() const { return AttackRangeBox; }
/// DamageType Getter
	TSubclassOf<UDamageType> GetDamageType() const { return DamageType; }
/// Weapon Getter
	AMonster_Weapon* GetWeaponInstance_Fst() const { return WeaponInstance; }
/// MTI Getter
	UMaterialInstanceDynamic* GetFstMTI() const { return Fst_MTI; }
	UMaterialInstanceDynamic* GetSndMTI() const { return Snd_MTI; }
	TArray<UMaterialInstanceDynamic*> GetMTIArray() const { return MTIArray; }
/// MTI Setter
	void SetFstMTI(UMaterialInstanceDynamic* newMTI) { Fst_MTI = newMTI; }
	void SetSndMTI(UMaterialInstanceDynamic* newMTI) { Snd_MTI = newMTI; }
	//TArray<UMaterialInstanceDynamic*> SetMTIArray() 
/// Property Setter
	void SetMonCurrentHp(const int newHp) { monNowHp = newHp; }
	void SetMonsterLive(const bool newBool) { isMonsterLive = newBool; }
};
