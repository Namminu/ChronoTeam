// Fill out your copyright notice in the Description page of Project Settings.


#include "Achor_Arrow.h"
#include "BaseMonster.h"
#include "Components/CapsuleComponent.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
AAchor_Arrow::AAchor_Arrow()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//RootComponent Setup
	Root= CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	RootComponent = Root;

	//Weapon Setup
	Arrow = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Arrow"));
	Arrow->SetupAttachment(Root);

	//CollisionBox Setup
	CollisionBox = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collision Box"));
	CollisionBox->SetupAttachment(Arrow);

	//Projectile Setup
	ProjectileComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Component"));
}

void AAchor_Arrow::OnAttackOverlapBegin(UPrimitiveComponent* const OverlappedComponent, 
	AActor* const otherActor,
	UPrimitiveComponent* const OtherComponent,
	int const OtherBodyIndex, bool const FromSweep, 
	FHitResult const& SweepResult)
{
	if (otherActor == this) return;

	if (otherActor->ActorHasTag("PLAYER"))
	{
		UE_LOG(LogTemp, Warning, TEXT("Arrow hits Player"));
		
		if (ABaseMonster* const mon = Cast<ABaseMonster>(GetOwner()))	//Get AtkDamage from BaseMonster
		{
			damageAmount = mon->GetMonAtk();
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Arrow Cast Failed to BaseMonster For Get DamageAmount"));
		}

		AController* MonsterC = GetInstigator()->GetController();	//Get Controller
		UGameplayStatics::ApplyDamage(otherActor, damageAmount, MonsterC, this, DamageType);
	}

	UE_LOG(LogTemp, Error, TEXT("Arrow Destory by overlap"));
	Destroy();	//destory when hits actor
}

void AAchor_Arrow::OnAttackOverlapEnd(UPrimitiveComponent* const OverlappedComponent,
	AActor* const otherActor, UPrimitiveComponent* const OtherComponent, int const OtherBodyIndex)
{
}

//void AAchor_Arrow::DestoryByDistance_Implementation(float distance)
//{
//	//Every Tick for Current Arrow Location
//	CurrentPosition = GetActorLocation();
//
//	//if ((CurrentPosition - StartPosition).X > distance)
//	//{
//	//	UE_LOG(LogTemp, Error, TEXT("Arrow Destory Time"));
//	//	Destroy();
//	//}
//
//
//}

// Called when the game starts or when spawned
void AAchor_Arrow::BeginPlay()
{
	Super::BeginPlay();
	
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AAchor_Arrow::OnAttackOverlapBegin);
	CollisionBox->OnComponentEndOverlap.AddDynamic(this, &AAchor_Arrow::OnAttackOverlapEnd);

	////Set Actor begin vector
	//StartPosition = GetActorLocation();
	//UE_LOG(LogTemp, Warning, TEXT("First Arrow Distance = %f"), arrowDistance);
	////Get Arrow Distance by BaseMonster
	//if (ABaseMonster* const mon = Cast<ABaseMonster>(GetOwner()))
	//{
	//	arrowDistance = mon->GetArrowDistance();
	//	UE_LOG(LogTemp, Warning, TEXT("After Casting Arrow Distance = %f"), arrowDistance);
	//}
	//else
	//{
	//	UE_LOG(LogTemp, Error, TEXT("Arrow Cast to BaseMonster has Failed!"));
	//}


}

// Called every frame
void AAchor_Arrow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//DestoryByDistance_Implementation(arrowDistance);
}

