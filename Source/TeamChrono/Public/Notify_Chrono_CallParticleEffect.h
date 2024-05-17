// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "Notify_Chrono_CallParticleEffect.generated.h"

/**
 * 
 */
UCLASS()
class TEAMCHRONO_API UNotify_Chrono_CallParticleEffect : public UAnimNotify
{
	GENERATED_BODY()
public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EFFECT", meta = (AllowPrivateAccess = "true"))
	class UParticleSystem* ParticleEffect;
};
