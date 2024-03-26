// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_CheckMontageisPlay.h"
#include "BaseEliteMonster.h"
#include "AIController.h"
#include <Blueprint/AIBlueprintHelperLibrary.h>
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_CheckMontageisPlay::UBTTask_CheckMontageisPlay(FObjectInitializer const& ObjectInitializer)
{
	NodeName = TEXT("Check Montage Playing");
}

EBTNodeResult::Type UBTTask_CheckMontageisPlay::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//Cast to Elite Monster
	auto const* const cont = OwnerComp.GetAIOwner();
	auto* const EliteMonster = Cast<ABaseEliteMonster>(cont->GetPawn());

	isPlaying = EliteMonster->GetMesh()->GetAnimInstance()->IsAnyMontagePlaying();
	//��Ÿ�ְ� ��� ���� �ƴ� ��
	if (!isPlaying)
	{
		UAIBlueprintHelperLibrary::GetAIController(EliteMonster)->GetBlackboardComponent()->SetValueAsBool("IsMontageEnd", true);
		return EBTNodeResult::Succeeded;
	}
	//��Ÿ�ְ� ��� ���� ��
	else
	{
		//UAIBlueprintHelperLibrary::GetAIController(EliteMonster)->GetBlackboardComponent()->SetValueAsBool("IsMontageEnd", false);
		return EBTNodeResult::Failed;
	}
}
