// Copyright Epic Games, Inc. All Rights Reserved.

#include "TeamChronoCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Components/WidgetComponent.h"
#include "StaminaWidget.h"
#include <algorithm>
#include "ABAnimInstance.h"
#include "ASword.h"
#include "PlayerArrow.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// ATeamChronoCharacter

ATeamChronoCharacter::ATeamChronoCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the con	troller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)


	StaminaBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("StaminaBar"));
	StaminaBar->SetupAttachment(GetMesh());

	// 월드공간 기준으로 배치될지(3D UI), 스크린 좌표 기준으로 배치될지(2D UI) 결정
	// Screen은 절대로 화면 밖으로 짤리지 않는다
	StaminaBar->SetWidgetSpace(EWidgetSpace::Screen);

	// ConstructorHelpers로 파일을 불러들여서 설정하는 익숙한 그것
	static ConstructorHelpers::FClassFinder<UUserWidget> UW = TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/WB_Stamina.WB_Stamina_C'");
	if (UW.Succeeded())
	{
		StaminaBar->SetWidgetClass(UW.Class);
		StaminaBar->SetDrawSize(FVector2D(-100.f, 200.f));
	}



	MaxCombo = 3;
	AttackEndComboState();

}

void ATeamChronoCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	ABAnim = Cast<UABAnimInstance>(GetMesh()->GetAnimInstance());

	ABAnim->OnMontageEnded.AddDynamic(this, &ATeamChronoCharacter::OnAttackMontageEnded);

	ABAnim->OnNextAttackCheck.AddLambda([this]() -> void
		{
			CanNextCombo = false;
			if (IsComboInputOn || IsComboPushOn)
			{
				CharacterMouseDirection();
				AttackStartComboState();
				ABAnim->JumpToAttackMontageSection(CurrentCombo);

			}
		});
}

void ATeamChronoCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	// 애니 이벤트 바인딩
	UAnimInstance* pAnimInst = GetMesh()->GetAnimInstance();
	if (pAnimInst != nullptr)
	{
		pAnimInst->OnPlayMontageNotifyBegin.AddDynamic(this, &ATeamChronoCharacter::HandleOnMontageNotifyBegin);
	}
	// 스테미나
	pcMoveStamina = pcStamina;
	GetWorldTimerManager().SetTimer(StaminaTimerHandle, this, &ATeamChronoCharacter::SetStamina, pcStaminaTimer, true);
	pcStamina = FMath::Clamp(pcStamina, 0, pcMaxStamina);

	
}



//////////////////////////////////////////////////////////////////////////
// Input

void ATeamChronoCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {

		// Dodging
		EnhancedInputComponent->BindAction(DodgeAction, ETriggerEvent::Started, this, &ATeamChronoCharacter::Dodge);
		//EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATeamChronoCharacter::Move);

		//Acttak
		//EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Started, this, &ATeamChronoCharacter::AttackClickStart);
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Started, this, &ATeamChronoCharacter::AttackClickStart);
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Completed, this, &ATeamChronoCharacter::AttackClickEnd);

		// Acttak 광클
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Started, this, &ATeamChronoCharacter::Attack);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void ATeamChronoCharacter::Attack()
{
	if (!m_bIsDodgingEnd && !IsQSkillBuilding)
	{
		if (IsAttacking)
		{
			if (CanNextCombo)
			{
				IsComboInputOn = true;

			}
		}
		else
		{
			AttackStartComboState();
			ABAnim->PlayAttackMontage();
			ABAnim->JumpToAttackMontageSection(CurrentCombo);
			IsAttacking = true;
			CharacterMouseDirection();

			FName WeaponSocket(TEXT("Weapon_Sword_Hand"));
			if (SwordInstance)
			{
				SwordInstance->AttachToComponent(GetMesh(),
					FAttachmentTransformRules::SnapToTargetNotIncludingScale,
					WeaponSocket);
			}
			// 원거리 캔슬
			IsNotLongAttacking();
		}
	}
	
	// GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("!!!!!!!")));
}

void ATeamChronoCharacter::AttackClickStart()
{
	if (!m_bIsDodgingEnd && !IsQSkillBuilding)
	{
		IsComboPushOn = true;
		//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("AttackClickStart")));
	}
	
}
void ATeamChronoCharacter::AttackClickEnd()
{
	//if (!m_bIsDodgingEnd && !IsQSkillBuilding)
	{
		IsComboPushOn = false;
		//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("AttackClickEnd")));
	}
	
}

void ATeamChronoCharacter::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	IsAttacking = false;
	AttackEndComboState();
}

void ATeamChronoCharacter::AttackStartComboState()
{
	CanNextCombo = true;
	IsComboInputOn = false;
	CurrentCombo = FMath::Clamp<int32>(CurrentCombo + 1, 1, MaxCombo);
}

void ATeamChronoCharacter::AttackEndComboState()
{
	IsComboInputOn = false;

	CanNextCombo = false;
	CurrentCombo = 0;

	FName WeaponSocket(TEXT("Weapon_Sword_Back"));
	if (SwordInstance)
	{
		SwordInstance->AttachToComponent(GetMesh(),
			FAttachmentTransformRules::SnapToTargetNotIncludingScale,
			WeaponSocket);
	}

	// 만약 끝났을때 마우스가 눌려있으면 다시 공격 시작
	if (IsComboPushOn)
	{
		Attack();
	}
}


void ATeamChronoCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	MoveRotation(MovementVector);
	if (Controller != nullptr && !m_bIsDodging && !IsAttacking && !IsQSkillBuilding && !LongAttacking)
	{

		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);


		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		//GEngine->AddOnScreenDebugMessage(1, 2.0f, FColor::Red, FString::Printf(TEXT("RightDirection.Rotation = %f"), RightDirection.Rotation().Yaw));
		


		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
		

		GEngine->AddOnScreenDebugMessage(1, 2.0f, FColor::Red, FString::Printf(TEXT("MovementVector.X = %f,  MovementVector.Y = %f"), MovementVector.X, MovementVector.Y));
	}
}



// 구르기
void ATeamChronoCharacter::Dodge()
{
	//GEngine->AddOnScreenDebugMessage(-0, 2.0f, FColor::Red, FString::Printf(TEXT("%f"), pcMoveStamina));
	if (!m_bIsDodging && !IsQSkillBuilding)
	{
		UE_LOG(LogTemp, Warning, TEXT("123"));
		// 현재 스테미너가 구르기 스테미너보다 있으면
		if (pcStamina >= pcDodgeStamina)
		{

			UAnimInstance* pAnimInst = GetMesh()->GetAnimInstance();
			if (pAnimInst != nullptr)
			{
				ABAnim->Montage_Stop(0);

				SetActorRotation(DodgeRotation);
				m_bIsDodging = true;
				m_bIsDodgingEnd = true;

				// 원거리 캔슬
				IsNotLongAttacking();

				RollAnimation();


				StaminaVariation(pcDodgeStamina);

			}
		}

	}
}

void ATeamChronoCharacter::AttachWeapon(TSubclassOf<AASword> Weapon)
{
	FName WeaponSocket(TEXT("Weapon_Sword_Back"));

	SwordInstance = GetWorld()->SpawnActor<AASword>(Weapon, GetMesh()->GetSocketTransform(WeaponSocket, ERelativeTransformSpace::RTS_World));

	if (SwordInstance)
	{

		SwordInstance->AttachToComponent(GetMesh(),
			FAttachmentTransformRules::SnapToTargetNotIncludingScale,
			WeaponSocket);
	}
}

void ATeamChronoCharacter::BowWeapon(TSubclassOf<APlayerArrow> Weapon)
{
	FName WeaponSocket(TEXT("Weapon_Arrow"));

	BowInstance = GetWorld()->SpawnActor<APlayerArrow>(Weapon, GetMesh()->GetSocketTransform(WeaponSocket, ERelativeTransformSpace::RTS_World));

	if (BowInstance)
	{

		BowInstance->AttachToComponent(GetMesh(),
			FAttachmentTransformRules::SnapToTargetNotIncludingScale,
			WeaponSocket);
	}

}



void ATeamChronoCharacter::StaminaVariation(float VariationStemina)
{
	if(0 < VariationStemina)
		Steminerdecreasing = true;

	pcStamina = pcStamina - VariationStemina;
	
	if (0 >= pcStamina)
	{
		pcStamina = 0;
	}
	else if (pcStamina >= pcMaxStamina)
	{
		pcStamina = pcMaxStamina;
	}
}




void ATeamChronoCharacter::HandleOnMontageNotifyBegin(FName a_nNotifyName, const FBranchingPointNotifyPayload& a_pBranchingPayload)
{
	// 구르기 애니메이션 알람 확인
	if (a_nNotifyName.ToString() == "Dodge")
	{
		m_bIsDodging = false;
	}
	if (a_nNotifyName.ToString() == "DodgeEnd")
	{
		m_bIsDodgingEnd = false;

	}
}

void ATeamChronoCharacter::IsNotLongAttacking_Implementation()
{
	 LongAttacking = false;
}


//스테미나 UI
void ATeamChronoCharacter::SetStamina()
{
	pcMoveStamina = FMath::Clamp(pcMoveStamina, pcStamina, pcMaxStamina);

	auto staminaWidget = Cast<UStaminaWidget>(StaminaBar->GetUserWidgetObject());

	if (Steminerdecreasing)
	{
		if (staminaWidget->GetVisibility() == ESlateVisibility::Hidden)
			staminaWidget->SetVisibility(ESlateVisibility::Visible);

		pcMoveStamina -= 2;
		if (pcMoveStamina <= pcStamina)
			Steminerdecreasing = false;
	}
	else if (pcStamina < pcMaxStamina)
	{
		pcStamina = (pcRecStamina * pcStaminaTimer) + pcStamina;


	}
	else if (pcMoveStamina >= pcMaxStamina)
	{
		staminaWidget->SetVisibility(ESlateVisibility::Hidden);
	}

	if (staminaWidget)
	{
		staminaWidget->StaminaBarPercent = pcMoveStamina / pcMaxStamina;
		//GEngine->AddOnScreenDebugMessage(-0, 2.0f, FColor::Red, FString::Printf(TEXT("%f"), pcMoveStamina));
	}
}

// 누른 방향 (구르기 방향)
void ATeamChronoCharacter::MoveRotation(FVector2D MovementVector)
{
	if (MovementVector.X == 1 && MovementVector.Y == 1)
	{
		DodgeRotation.Yaw = 90;
	}
	else if (MovementVector.X == 1 && MovementVector.Y == -1)
	{
		DodgeRotation.Yaw = 180;
	}
	else if (MovementVector.X == -1 && MovementVector.Y == -1)
	{
		DodgeRotation.Yaw = -90;
	}
	else if (MovementVector.X == -1 && MovementVector.Y == 1)
	{
		DodgeRotation.Yaw = 0;
	}
	else if (MovementVector.X == 1 && MovementVector.Y == 0)
	{
		DodgeRotation.Yaw = 135;
	}
	else if (MovementVector.X == -1 && MovementVector.Y == 0)
	{
		DodgeRotation.Yaw = -45;
	}
	else if (MovementVector.X == 0 && MovementVector.Y == 1)
	{
		DodgeRotation.Yaw = 45;
	}
	else if (MovementVector.X == 0 && MovementVector.Y == -1)
	{
		DodgeRotation.Yaw = -135;
	}
}