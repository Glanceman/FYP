// Fill out your copyright notice in the Description page of Project Settings.


#include "./SEnemyBaseController.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "FYP/Character/SCharacterBase.h"
#include "Perception/AIPerceptionComponent.h"

ASEnemyBaseController::ASEnemyBaseController()
{
	AIPerceptionComponent=CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerception"));
	// SightConfig=CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	
}

void ASEnemyBaseController::OnPerception(AActor* Actor, FAIStimulus Stimulus)
{
	//UE_LOG(LogTemp,Warning,TEXT("Perception"));
	if(Stimulus.WasSuccessfullySensed())
	{
		Blackboard->SetValueAsObject(TEXT("TargetActor"),Actor);
		UE_LOG(LogTemp,Warning,TEXT("Sense coming"));
	}else
	{
		Blackboard->ClearValue(TEXT("TargetActor"));
		UE_LOG(LogTemp,Warning,TEXT("Sense Leaving"));
	}
	Blackboard->SetValueAsVector(TEXT("InvestigateLocation"),Actor->GetActorLocation());
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
	
	// SightConfig->DetectionByAffiliation.bDetectEnemies=bCheckEnemy;
	// SightConfig->DetectionByAffiliation.bDetectFriendlies = bCheckFriend;
	// SightConfig->DetectionByAffiliation.bDetectNeutrals = bCheckNeutral;
	// SightConfig->SightRadius=SightRadius;
	// SightConfig->LoseSightRadius=LoseSightRadius;
	// SightConfig->PeripheralVisionAngleDegrees=PeripheralVisionAngleDegrees;
	// AIPerceptionComponent->ConfigureSense(*SightConfig);
	// AIPerceptionComponent->SetDominantSense(SightConfig->GetSenseImplementation());
	AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this,&ASEnemyBaseController::OnPerception);

	ASCharacterBase* ControlledCharacter=static_cast<ASCharacterBase*>(GetPawn());
	if(ControlledCharacter)
	{
		TeamID=ControlledCharacter->TeamID;
	}
	
	
}

FGenericTeamId ASEnemyBaseController::GetGenericTeamId() const
{
	return TeamID;
}
//
ETeamAttitude::Type ASEnemyBaseController::GetTeamAttitudeTowards(const AActor& Other) const
{
	const ASCharacterBase* OtherCharacter= Cast<ASCharacterBase>(&Other);
	if(OtherCharacter==nullptr)
	{
		return ETeamAttitude::Neutral;	
	}
	
	const IGenericTeamAgentInterface* IOtherCharacter = Cast<IGenericTeamAgentInterface>(OtherCharacter);
	const IGenericTeamAgentInterface* IOtherController = Cast<IGenericTeamAgentInterface>(OtherCharacter->GetController());
	if(IOtherCharacter==nullptr && IOtherController==nullptr)
	{
		return ETeamAttitude::Neutral;	
	}

	FGenericTeamId OtherCharacterTeamID;
	if(IOtherController)
	{
		OtherCharacterTeamID=IOtherController->GetGenericTeamId();
	}else if(IOtherCharacter)
	{
		OtherCharacterTeamID=IOtherCharacter->GetGenericTeamId();
	}
	
	//compare id vs ai controller id
	if(OtherCharacterTeamID==0)
	{
		return ETeamAttitude::Neutral;	
	}
	if(OtherCharacterTeamID!=TeamID)
	{
		return ETeamAttitude::Hostile;	
	}
	if(OtherCharacterTeamID==TeamID)
	{
		return ETeamAttitude::Friendly;	
	}

	return ETeamAttitude::Neutral;	
}


