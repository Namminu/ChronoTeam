// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Fighter_Fst_Marble.generated.h"

UCLASS()
class TEAMCHRONO_API AFighter_Fst_Marble : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFighter_Fst_Marble();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void SetEffectToBarrier();

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* RootScene;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FST GIMIC", meta = (AllowPrivateAccess = "true"))
	class USphereComponent* RootSphere;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FST GIMIC", meta = (AllowPrivateAccess = "true"))
	class UNiagaraComponent* Fst_Effect;

public:
	UFUNCTION(BlueprintCallable)
	class UNiagaraComponent* GetFstEffect() const { return Fst_Effect; }

	UFUNCTION(BlueprintCallable)
	void SetFstEffect(class UNiagaraComponent* const newEffect) { Fst_Effect = newEffect; }
};
