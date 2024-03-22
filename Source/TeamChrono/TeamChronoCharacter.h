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

	UPROPERTY(VisibleAnywhere)
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

	// �� ����
	// static AActor* CurrentSword;


public:
	// �޺� �Է��� ���� �ִ��� ����
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	bool IsComboInputOn;



	// UPROPERTY(VisibleAnywhere, Category = Weapon)
	// class AABWeapon* CurrentWeapon;

private:

	// �����̴� ���׹̳� ǥ�� �� ����
	float pcMoveStamina;

	//���׹̳� Ÿ�̸�
	FTimerHandle StaminaTimerHandle;

	void SetStamina();

	bool Steminerdecreasing = false;

	void MoveRotation(FVector2D MovementVector);

	//������ ���� ����
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = MoveRotation, Meta = (AllowPrivateAccess = true))
	FRotator DodgeRotation;
public:
	ATeamChronoCharacter();


	// ȸ�� ���
	void Dodge();
	bool m_bIsDodging = false;
	bool m_bIsDodgingEnd = false;
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void RollAnimation();

	//�ִ� ���׹̳�
	UPROPERTY(EditAnywhere, Category = "Stamina")
	float pcMaxStamina = 100.0f;
	// ���� ���׹̳�
	UPROPERTY(EditAnywhere, Category = "Stamina")
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


	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Weapon;

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
};