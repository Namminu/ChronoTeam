// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_IsShieldOn.h"
#include "BaseEliteMonster.h"
#include "AIController.h"
#include <Blueprint/AIBlueprintHelperLibrary.h>
#include "BehaviorTree/BlackboardComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"

UBTTask_IsShieldOn::UBTTask_IsShieldOn(FObjectInitializer const& ObjectInitializer)
{
	NodeName = TEXT("Check is Shield On");
	isShieldOn = false;
}

EBTNodeResult::Type UBTTask_IsShieldOn::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//Cast to Elite Monster
	auto const* const cont = OwnerComp.GetAIOwner();
	auto* const EliteMonster = Cast<ABaseEliteMonster>(cont->GetPawn());

	if (!isShieldOn)
	{
		UE_LOG(LogTemp, Warning, TEXT("Set Shield On"));
		EliteMonster->GetSpecificEffect()->Activate();
		//EliteMonster->GetWeaponInstance_Fst()->GetWeaponMesh()->SetRenderCustomDepth(true);
	}
	else if (isShieldOn)
	{
		UE_LOG(LogTemp, Warning, TEXT("Set Shield Off"));
		EliteMonster->GetSpecificEffect()->Deactivate();
		//EliteMonster->GetWeaponInstance_Fst()->GetWeaponMesh()->SetRenderCustomDepth(false);
	}
	return EBTNodeResult::Succeeded;
}
