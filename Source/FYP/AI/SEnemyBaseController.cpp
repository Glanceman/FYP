// Fill out your copyright notice in the Description page of Project Settings.


#include "./SEnemyBaseController.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"

ASEnemyBaseController::ASEnemyBaseController()
{
	AIPerceptionComponent=CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerception"));
	SightConfig=CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	
	AIPerceptionComponent->ConfigureSense(*SightConfig);
	AIPerceptionComponent->SetDominantSense(UAISenseConfig_Sight::StaticClass());
}

void ASEnemyBaseController::OnPerception(AActor* Actor, FAIStimulus Stimulus)
{
	//UE_LOG(LogTemp,Warning,TEXT("Perception"));
	Blackboard->SetValueAsObject(TEXT("TargetActor"),Actor);
}

void ASEnemyBaseController::BeginPlay()
{
	Super::BeginPlay();
	if(SEnemyBase_BT==nullptr)
	{
		UE_LOG(LogTemp,Warning,TEXT("No behavior tree for ASEnemyBaseController"));
		return;
	}
	RunBehaviorTree(SEnemyBase_BT);
	AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this,&ASEnemyBaseController::OnPerception);

	SightConfig->DetectionByAffiliation.bDetectEnemies=true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = false;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
	SightConfig->SightRadius=SightRadius;
	SightConfig->LoseSightRadius=LoseSightRadius;
	SightConfig->PeripheralVisionAngleDegrees=PeripheralVisionAngleDegrees;
}
