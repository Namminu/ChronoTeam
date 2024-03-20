// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_StopCurrentMontage.h"
#include "BaseEliteMonster.h"
#include "AIController.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"

UBTTask_StopCurrentMontage::UBTTask_StopCurrentMontage(FObjectInitializer const& ObjectInitializer)
{
	NodeName = TEXT("Stop Current Montage");
}

EBTNodeResult::Type UBTTask_StopCurrentMontage::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//Cast to Elite Monster
	auto const* const cont = OwnerComp.GetAIOwner();
	auto* const EliteMonster = Cast<ABaseEliteMonster>(cont->GetPawn());

	//Get Current Playing AnimMontage for Pause
	UAnimMontage* currentMontage = EliteMonster->GetMesh()->GetAnimInstance()->GetCurrentActiveMontage();
	EliteMonster->GetMesh()->GetAnimInstance()->Montage_Stop(0.f, currentMontage);

	//if Big Attack Effect is on Activate - Get Off
	if (EliteMonster->GetSpecificEffect()->IsActive())
	{
		UE_LOG(LogTemp, Error, TEXT("Specific Effect get Off"));
		EliteMonster->GetSpecificEffect()->Deactivate();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Specific Effect if Not Activate"));
	}

	return EBTNodeResult::Succeeded;
}
