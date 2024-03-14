// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BehaviorTree.h"
#include "GameFramework/Character.h"
#include "CombatInterface.h"
#include "Animation/AnimMontage.h"
#include "Monster_Weapon.h"
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
	void mon_Death();
	void mon_Destroy();

	//Create Dynamic Material Instance Function
	void CreateMTI();

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
	//���� ��Ʈ�ڽ�
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collision, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* WeaponCollisionBox;
	//����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WEAPON", meta = (AllowPrivateAccess = "true"))
	AMonster_Weapon* WeaponInstance;
	//���ݹ��� ��Ʈ�ڽ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Collision, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* AttackRangeBox;

///
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "EFFECT", meta = (AllowPrivateAccess = "true"))
	class UNiagaraComponent* NiagaraAttackEffect;

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

	UFUNCTION()
	void OnRangeOverlapBegin(UPrimitiveComponent* const OverlappedComponent,
		AActor* const otherActor,
		UPrimitiveComponent* const OtherComponent,
		int const OtherBodyIndex,
		bool const FromSweep,
		FHitResult const& SweepResult);

	UFUNCTION()
	void OnRangeOverlapEnd(UPrimitiveComponent* const OverlappedComponent,
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

public:
	int GetMonSpeed() const { return monSpeed; }	
	int GetMonAtkRange() const { return monAtkRange; }	
	int GetMonCurrentHp() const { return monNowHp; } 
	int GetMonAtk() const { return monAtk; }

	UNiagaraComponent* GetAttackEffect() const { return NiagaraAttackEffect; }
	// 
	//float GetArrowDistance() const { return arrow_Distance; }
	
};
