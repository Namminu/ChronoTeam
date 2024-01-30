// Fill out your copyright notice in the Description page of Project Settings.


#include "AI_Controller_.h"
#include "BaseMonster.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "TeamChrono/TeamChronoCharacter.h"

AAI_Controller_::AAI_Controller_(FObjectInitializer const& ObjectInitializer)
{
	SetupPerceptionSystem();
}

//Monster BT ���� �Լ�
void AAI_Controller_::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if (ABaseMonster* const baseMonster = Cast<ABaseMonster>(InPawn))
	{
		if (UBehaviorTree* const  BTree = baseMonster->GetBehaviorTree())
		{
			UBlackboardComponent* bb;
			UseBlackboard(BTree->BlackboardAsset, bb);
			Blackboard = bb;
			RunBehaviorTree(BTree);
		}
	}
}

//Target �ν� �ý��� ����
void AAI_Controller_::SetupPerceptionSystem()
{
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	if (SightConfig)
	{
		SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Component")));
		SightConfig->SightRadius = 500.f;
		SightConfig->LoseSightRadius = SightConfig->SightRadius + 25.f;
		SightConfig->PeripheralVisionAngleDegrees = 90.f;
		SightConfig->SetMaxAge(5.f);
		SightConfig->AutoSuccessRangeFromLastSeenLocation = 520.f;
		SightConfig->DetectionByAffiliation.bDetectEnemies = true;
		SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
		SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

		GetPerceptionComponent()->SetDominantSense(*SightConfig->GetSenseImplementation());
		GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &AAI_Controller_::OnTargetDetected);
		GetPerceptionComponent()->ConfigureSense(*SightConfig);
	}
}

//�÷��̾�(Target)�� �������� �� ȣ��Ǵ� �Լ�
void AAI_Controller_::OnTargetDetected(AActor* actor, FAIStimulus const stimulus)
{
	if (auto* const ch = Cast<ATeamChronoCharacter>(actor))
	{
		//�÷��̾ �����Ǹ� true, �������/�Ⱥ��̸� false
		GetBlackboardComponent()->SetValueAsBool("CanSeePlayer", stimulus.WasSuccessfullySensed());
	}
}
