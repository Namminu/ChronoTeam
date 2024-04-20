// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "TeamChronoCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config = Game)
class ATeamChronoCharacter : public ACharacter
{
	GENERATED_BODY()
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Dodge Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* DodgeAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* AttackAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ESkillAction;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = StaminaBar, meta = (AllowPrivateAccess = "true"))
	class UWidgetComponent* StaminaBar;


	void Attack();
	void AttackClickStart();
	void AttackClickEnd();

	// ���� ��Ÿ�� ���� ��
	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	// ���� ���� �޺� ����
	void AttackStartComboState();

	// ���� ���� �޺� ����
	void AttackEndComboState();

	// ���������� Ȯ��
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	bool IsAttacking;

	// ���� �޺�
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	bool CanNextCombo;



	// ���� �޺�
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	int32 CurrentCombo;

	// �ƽ� �޺�
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	int32 MaxCombo;

	UPROPERTY()
	class UABAnimInstance* ABAnim;




public:
	// �޺� �Է��� ���� �ִ��� ����
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	bool IsComboInputOn;

	// �޺� �Է��� ���� �ִ��� ����
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	bool IsComboPushOn = false;



	// UPROPERTY(VisibleAnywhere, Category = Weapon)
	// class AABWeapon* CurrentWeapon;
	
	//������ ���� ����
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = MoveRotation, Meta = (AllowPrivateAccess = true))
	FRotator DodgeRotation;

private:

	// �����̴� ���׹̳� ǥ�� �� ����
	float pcMoveStamina;

	//���׹̳� Ÿ�̸�
	FTimerHandle StaminaTimerHandle;

	void SetStamina();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stamina", Meta = (AllowPrivateAccess = true))
	bool Steminerdecreasing = false;
	
	// ���׹̳� ���� Ű��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stamina", Meta = (AllowPrivateAccess = true))
	bool StaminaOnOff = false;

	void MoveRotation(FVector2D MovementVector);


	// �ִ� ü���� �ִ�
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = HP, Meta = (AllowPrivateAccess = true))
	int p_FullMaxHp = 10;

	// ���� �ִ� ü��
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = HP, Meta = (AllowPrivateAccess = true))
	int P_MaxHP = 4;

	// ���� ü��
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = HP, Meta = (AllowPrivateAccess = true))
	int P_CurrentHP;
	
	//�ִ� ���׹̳�
	UPROPERTY(EditAnywhere, Category = "Stamina")
	float pcMaxStamina = 100.0f;
	// ���� ���׹̳�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stamina", Meta = (AllowPrivateAccess = true))
	float pcStamina = 100.0f;
	// ���׹̳�UI �ε巴�� ���� �ð�
	UPROPERTY(EditAnywhere, Category = "Stamina")
	float pcStaminaTimer = 0.05f;

	// �ڵ� ȸ��
	UPROPERTY(EditAnywhere, Category = "Stamina")
	float pcRecStamina = 2.0f;
	//������ ���׹̳�
	UPROPERTY(EditAnywhere, Category = "Stamina")
	float pcDodgeStamina = 20.0f;

	// ���� ȸ�� ���׹̳�
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stamina", Meta = (AllowPrivateAccess = true))
	float AttackStaminaRecovery = 5.0f;

	// e ��ų ���׹̳�
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stamina", Meta = (AllowPrivateAccess = true))
	float ESkillStamina = 25.0f;

	// e ��ų ��Ÿ��
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ESkill", Meta = (AllowPrivateAccess = true))
	int ESkillCoolTime = 5;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ESkill", Meta = (AllowPrivateAccess = true))
	int ESkillBackTime = 4;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ESkill", Meta = (AllowPrivateAccess = true))
	bool EskillCheck;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ESkill", Meta = (AllowPrivateAccess = true))
	bool IsESkillDoing;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Climbing", Meta = (AllowPrivateAccess = true))
	bool IsClimbing = false;

	// ��Ŭ�� ���Ÿ� ������ Ȯ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LongAttack", Meta = (AllowPrivateAccess = true))
	bool LongAttacking = false;

	// ���Ÿ� ���׹̳�
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stamina", Meta = (AllowPrivateAccess = true))
	float LongAttackStamina = 10.0f;
	// ȸ�� ���
	void Dodge();

	// ��Ŭ�� ���Ÿ� ������ Ȯ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TabSkill", Meta = (AllowPrivateAccess = true))
	bool IsTabSkillMoving = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WEAPON", meta = (AllowPrivateAccess = "true"))
	class AASword* SwordInstance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WEAPON", meta = (AllowPrivateAccess = "true"))
	class APlayerArrow* BowInstance;

	bool m_bIsDodgingEnd = false;

	// ����
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "����", Meta = (AllowPrivateAccess = true))
	bool Nodamage = false;



	// Q ��ų �������� ���׹̳�
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stamina", Meta = (AllowPrivateAccess = true))
	float QSkillStamina = 25.0f;

	// Q ��ų ������ ���׹̳�
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stamina", Meta = (AllowPrivateAccess = true))
	float QSkillingStamina = 5.0f;

	// Q ��ų ��� �Ⱦ��� ������ ���׹̳�
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stamina", Meta = (AllowPrivateAccess = true))
	float QSkillEndStamina = 10.0f;
	
	
	// Tab��ų ������ ���׹̳�
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stamina", Meta = (AllowPrivateAccess = true))
	float TabSkillingStamina = 5.0f;

public:


	//���� ���� ȣ�� �Լ�
	UFUNCTION(BlueprintCallable)
	void AttachWeapon(TSubclassOf<AASword> Weapon);

	//Ȱ ���� ȣ�� �Լ�
	UFUNCTION(BlueprintCallable)
	void BowWeapon(TSubclassOf<APlayerArrow> Weapon);

	// ���׹̳� ����(��ų ���ų� ȸ���ϰų�)
	UFUNCTION(BlueprintCallable)
	void StaminaVariation(float VariationStemina);






	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category = Dodge)
	bool m_bIsDodging = false;

	ATeamChronoCharacter();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QSkill")
	bool IsQSkillBuilding;

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void RollAnimation();

	// ���콺 ���� �ٶ󺸴� �ڵ�
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void CharacterMouseDirection();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void HitDetect();

protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);


protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// To add mapping context
	virtual void BeginPlay();

	virtual void PostInitializeComponents();

public:
	UFUNCTION()
	void HandleOnMontageNotifyBegin(FName a_nNotifyName, const FBranchingPointNotifyPayload& a_pBranchingPayload);

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	UFUNCTION(BlueprintCallable)
	void IsNotDodging()  { m_bIsDodgingEnd = false;  m_bIsDodging = false;}

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void IsNotLongAttacking();
};