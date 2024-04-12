// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_BossCheckMontagePlaying.h"
#include "BossAIController.h"
#include "Base_Boss.h"
#include <Blueprint/AIBlueprintHelperLibrary.h>
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_BossCheckMontagePlaying::UBTTask_BossCheckMontagePlaying(FObjectInitializer const& ObjectInitializer)
{
	NodeName = TEXT("Boss Check Montage is Playing");
}

EBTNodeResult::Type UBTTask_BossCheckMontagePlaying::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto const* const cont = OwnerComp.GetAIOwner();
	auto* const BossMonster = Cast<ABase_Boss>(cont->GetPawn());

	isPlaying = BossMonster->GetMesh()->GetAnimInstance()->IsAnyMontagePlaying();

	//��Ÿ�ְ� ��� ���� �ƴ� ��
	if (!isPlaying)
	{
		UAIBlueprintHelperLibrary::GetAIController(BossMonster)->GetBlackboardComponent()->SetValueAsBool("IsMontageEnd", true);
		return EBTNodeResult::Succeeded;
	}
	//��Ÿ�ְ� ��� ���� ��
	else
	{
		return EBTNodeResult::Failed;
	}
}