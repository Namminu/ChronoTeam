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

	UPROPERTY(VisibleAnywhere)
	class UWidgetComponent* StaminaBar;


	void Attack();
	void AttackClickStart();
	void AttackClickEnd();
	// 공격 몽타주 종료 시
	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	// 공격 시작 콤보 상태
	void AttackStartComboState();

	// 공격 종료 콤보 상태
	void AttackEndComboState();

	// 공격중인지 확인
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	bool IsAttacking;

	// 다음 콤보
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	bool CanNextCombo;



	// 현재 콤보
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	int32 CurrentCombo;

	// 맥스 콤보
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	int32 MaxCombo;

	UPROPERTY()
	class UABAnimInstance* ABAnim;

	// 검 엑터
	// static AActor* CurrentSword;


public:
	// 콤보 입력이 켜져 있는지 여부
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	bool IsComboInputOn;



	// UPROPERTY(VisibleAnywhere, Category = Weapon)
	// class AABWeapon* CurrentWeapon;

private:

	// 움직이는 스테미나 표시 할 변수
	float pcMoveStamina;

	//스테미나 타이머
	FTimerHandle StaminaTimerHandle;

	void SetStamina();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stamina", Meta = (AllowPrivateAccess = true))
	bool Steminerdecreasing = false;

	void MoveRotation(FVector2D MovementVector);

	//구르는 방향 저장
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = MoveRotation, Meta = (AllowPrivateAccess = true))
	FRotator DodgeRotation;

	// 최대 체력의 최대
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = HP, Meta = (AllowPrivateAccess = true))
	int p_FullMaxHp = 12;

	// 현재 최대 체력
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = HP, Meta = (AllowPrivateAccess = true))
	int P_MaxHP = 4;

	// 현재 체력
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = HP, Meta = (AllowPrivateAccess = true))
	int P_CurrentHP;

	//최대 스테미너
	UPROPERTY(EditAnywhere, Category = "Stamina")
	float pcMaxStamina = 100.0f;
	// 현재 스테미너
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stamina", Meta = (AllowPrivateAccess = true))
	float pcStamina = 100.0f;
	// 스테미너UI 부드럽게 변경 시간
	UPROPERTY(EditAnywhere, Category = "Stamina")
	float pcStaminaTimer = 0.05f;

	// 자동 회복
	UPROPERTY(EditAnywhere, Category = "Stamina")
	float pcRecStamina = 2.0f;
	//구르기 스테미너
	UPROPERTY(EditAnywhere, Category = "Stamina")
	float pcDodgeStamina = 20.0f;

	// e 스킬 스테미너
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ESkill", Meta = (AllowPrivateAccess = true))
	float ESkillStamina = 25.0f;

	// e 스킬 쿨타임
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ESkill", Meta = (AllowPrivateAccess = true))
	int ESkillCoolTime = 5;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ESkill", Meta = (AllowPrivateAccess = true))
	int ESkillBackTime = 4;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ESkill", Meta = (AllowPrivateAccess = true))
	bool EskillCheck;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ESkill", Meta = (AllowPrivateAccess = true))
	bool IsESkillDoing;

	// 회피 기능
	void Dodge();


	bool m_bIsDodgingEnd = false;
public:

	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category = Dodge)
	bool m_bIsDodging = false;

	ATeamChronoCharacter();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QSkill")
	bool IsQSkillBuilding;

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void RollAnimation();

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

	UFUNCTION(BlueprintCallable)
	void isNotDodging()  { m_bIsDodgingEnd = false;  m_bIsDodging = false;}

};