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

	//�⺻ ���� �Լ�
	void AttackStart() const;
	void AttackEnd() const;

	//��ó ���� - ȭ�� �߻� �Լ�
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void FireArrow();

	float TakeDamage(float DamageAmount,
		struct FDamageEvent const& DamageEvent, 
		AController* EventInstigator, 
		AActor* DamageCauser) override;

	//Damage Flash �Լ� - ��¦��
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void DamageFlash();

	//���� �� ���� ���� �Լ�
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void Change_Opacity(float StartAlpha, float EndAlpha);

	//���� ���� ȣ�� �Լ�
	UFUNCTION(BlueprintCallable)
	void AttachWeapon(TSubclassOf<AMonster_Weapon> Weapon, FName socketName);

	//���̾ư��� ����Ʈ ȣ�� �Լ�
	UFUNCTION(BlueprintCallable)
	void CallNiagaraEffect(UNiagaraComponent* NiaEffect);

	//���� ��� ȣ�� �Լ�
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
	//�����̺�� Ʈ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	UBehaviorTree* BTree;
	//���� �ִϸ��̼� ��Ÿ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation, meta =(AllowPrivateAccess = "true"))
	UAnimMontage* AtkMontage;
	//���� �ִϸ��̼� ��Ÿ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation, meta = (AllowPrivateAccess = "true"))
	UAnimMontage* CreateMontage;
	//��� �ִϸ��̼� ��Ÿ��
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
	////���� ��Ʈ�ڽ�
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Collision, meta = (AllowPrivateAccess = "true"))
	//class UBoxComponent* WeaponCollisionBox;
	//����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WEAPON", meta = (AllowPrivateAccess = "true"))
	class AMonster_Weapon* WeaponInstance;
	//���ݹ��� ��Ʈ�ڽ�
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
	//���� �ִ� ü��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MONSTER", meta = (AllowPrivateAccess = "true"))
	int monMaxHp;
	//���� ���� ü��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MONSTER", meta = (AllowPrivateAccess = "true"))
	int monNowHp;
	//���� �̵� �ӵ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MONSTER", meta = (AllowPrivateAccess = "true"))
	int monSpeed;	
	//���� ���� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MONSTER", meta = (AllowPrivateAccess = "true"))
	int monAtkRange;
	//���� ���ݷ�
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MONSTER", meta = (AllowPrivateAccess = "true"))
	int monAtk;

	////��ó ���� ȭ�� �Ÿ�
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MONSTER_ACHOR", meta = (AllowPrivateAccess = "true"))
	//float arrow_Distance;

	//���� ���� �ð�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MONSTER", meta = (AllowPrivateAccess = "true"))
	float duration;

	//������ ��¦�� �ݺ� Ƚ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DAMAGE FLASH", meta = (AllowPrivateAccess = "true"))
	float flashCount;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UDamageType> DamageType;

	//���� ���� float
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
