// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseMonster.h"
#include "Components/BoxComponent.h"
#include <TeamChrono/TeamChronoCharacter.h>

// Sets default values
ABaseMonster::ABaseMonster() : RightFirstCollisionBox{ CreateDefaultSubobject<UBoxComponent>(TEXT("RightFirstCollisionBox")) }
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (RightFirstCollisionBox)	//��Ʈ�ڽ� ����
	{
		RightFirstCollisionBox->SetBoxExtent(FVector(5.f));
		FAttachmentTransformRules const Rules{
			EAttachmentRule::SnapToTarget,	//location
			EAttachmentRule::SnapToTarget,	//rotation
			EAttachmentRule::KeepWorld,		//World Scale
			false	// Not default Attach to body
		};
		RightFirstCollisionBox->AttachToComponent(GetMesh(), Rules, "hand_r_Socket");
		RightFirstCollisionBox->SetRelativeLocation(FVector(-7.f, 0.f, 0.f));
	}
}

// Called when the game starts or when spawned
void ABaseMonster::BeginPlay()
{
	Super::BeginPlay();

	RightFirstCollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ABaseMonster::OnAttackOverlapBegin);
	RightFirstCollisionBox->OnComponentEndOverlap.AddDynamic(this, &ABaseMonster::OnAttackOverlapEnd);

	//���� �� �ִϸ��̼� ���
	//Create_Opacity();
	//if (Create_Opacity()) { PlayAnimMontage(CreateMontage); }
	PlayAnimMontage(CreateMontage);
}

void ABaseMonster::OnAttackOverlapBegin(UPrimitiveComponent* const OverlappedComponent,
	AActor* const otherActor,
	UPrimitiveComponent* const OtherComponent,
	int const OtherBodyIndex, bool const FromSweep,
	FHitResult const& SweepResult)
{
	if (otherActor == this) return;		//��Ʈ�ڽ��� �ڱ� �ڽſ��� ����� ��� �ƹ� ����x

	if (otherActor->ActorHasTag("PLAYER"))	//��Ʈ�ڽ��� �÷��̾�� ����� ��� = �÷��̾� ���� ��
	{
		//auto const NewHealth = Enemy->GetHealth() - Enemy->GetMaxHealth() * 0.1f;
		//Enemy->SetHealth(NewHealth);

		UE_LOG(LogTemp, Warning, TEXT("Monster hit Player"));
	}
}

void ABaseMonster::OnAttackOverlapEnd(UPrimitiveComponent* const OverlappedComponent, 
	AActor* const otherActor, 
	UPrimitiveComponent* const OtherComponent, 
	int const OtherBodyIndex)
{

}

// Called every frame
void ABaseMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseMonster::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

int ABaseMonster::MeleeAttack_Implementation()
{
	if (AtkMontage)
	{
		PlayAnimMontage(AtkMontage);
	}
	return 0;
}

bool ABaseMonster::Create_Opacity()
{
	//���� �ִϸ��̼� ����
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
	SetActorTickEnabled(false);

	// ���� ��ȭ ����
	float CurrentTime = 0.0f;
	float StartAlpha = 0.0f;
	float EndAlpha = 1.0f;

	TArray<UMaterialInstanceDynamic*> DynamicMaterials;

	// �޽��� ��� ���׸��� �ν��Ͻ� ��������
	TArray<UMaterialInterface*> BaseMaterials;
	BaseMaterials = GetMesh()->GetMaterials();
	for (UMaterialInterface* BaseMaterial : BaseMaterials)
	{
		UMaterialInstanceDynamic* DynamicMaterial = UMaterialInstanceDynamic::Create(BaseMaterial, GetOwner());
		if (DynamicMaterial)
		{
			DynamicMaterials.Add(DynamicMaterial);
		}
	}

	while (CurrentTime < duration)
	{
		// ���� ����
		float Alpha = FMath::Lerp(StartAlpha, EndAlpha, CurrentTime / duration);

		// ���׸��� �ν��Ͻ��� ���� ����
		for (UMaterialInstanceDynamic* DynamicMaterial : DynamicMaterials)
		{
			DynamicMaterial->SetScalarParameterValue(TEXT("Opacity"), Alpha);
		}

		// ��� �ð� ������Ʈ
		CurrentTime += GetWorld()->GetDeltaSeconds();

		// ���� �����ӱ��� ���
		GetOwner()->GetWorld()->Tick(ELevelTick::LEVELTICK_All, GetWorld()->GetDeltaSeconds());
	}

	// ���� �ִϸ��̼� ����
	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);
	SetActorTickEnabled(true);

	return true;	//���� ������ ������ true �� ��ȯ -> ���� �ִϸ��̼� ���
}

void ABaseMonster::AttackStart() const
{
	RightFirstCollisionBox->SetCollisionProfileName("Fist");
	RightFirstCollisionBox->SetNotifyRigidBodyCollision(true);
}

void ABaseMonster::AttackEnd() const
{
	RightFirstCollisionBox->SetCollisionProfileName("Fist");
	RightFirstCollisionBox->SetNotifyRigidBodyCollision(false);
}

UAnimMontage* ABaseMonster::GetAtkMontage() const
{ 
	return AtkMontage; 
}

UBehaviorTree* ABaseMonster::GetBehaviorTree() const
{ 
	return BTree;
}