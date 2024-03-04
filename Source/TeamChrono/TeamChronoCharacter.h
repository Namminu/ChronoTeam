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

UCLASS(config=Game)
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
	UInputAction* ActtackAction;

	UPROPERTY(VisibleAnywhere)
	class UWidgetComponent* StaminaBar;

private:

	// 움직이는 스테미나 표시 할 변수
	float pcMoveStamina;

	//스테미나 타이머
	FTimerHandle StaminaTimerHandle;

	void SetStamina();

	bool Steminerdecreasing = false;
public:
	ATeamChronoCharacter();
	
	// 구르기 몽타주
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	UAnimMontage* m_pDodgeMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dodge")
	float DodgeSpeed = 2000;
	// 회피 기능
	void Dodge();
	bool m_bIsDodging = false;

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void RollAnimation();

	//최대 스테미너
	UPROPERTY(EditAnywhere, Category = "Stamina")
	float pcMaxStamina = 100.0f;
	// 현재 스테미너
	UPROPERTY(EditAnywhere, Category = "Stamina")
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

public:
	UFUNCTION()
	void HandleOnMontageNotifyBegin(FName a_nNotifyName, const FBranchingPointNotifyPayload& a_pBranchingPayload);

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }


};

