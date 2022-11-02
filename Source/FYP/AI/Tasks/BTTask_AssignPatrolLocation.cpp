// Fill out your copyright notice in the Description page of Project Settings.


#include "./BTTask_AssignPatrolLocation.h"

#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_AssignPatrolLocation::UBTTask_AssignPatrolLocation()
{
	NodeName=TEXT("AssignPatrolLocation");
}

EBTNodeResult::Type UBTTask_AssignPatrolLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	FName KeyName=GetSelectedBlackboardKey();
	UBlackboardComponent* BlackboardComponent=OwnerComp.GetBlackboardComponent();
	UNavigationSystemV1* NavSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(this);
	FVector ControlledPawnLocation = OwnerComp.GetAIOwner()->GetPawn()->GetActorLocation();
	if(!NavSystem)
	{
		UE_LOG(LogTemp,Warning,TEXT("NavSystem Null"));
		return EBTNodeResult::Failed;
	}
	FNavLocation ResultLocation;
	bool bSucceed = NavSystem->GetRandomPointInNavigableRadius(ControlledPawnLocation,Radius,ResultLocation);
	if(bSucceed)
	{
		BlackboardComponent->SetValueAsVector(KeyName,ResultLocation);
		return EBTNodeResult::Succeeded;		
	}
	UE_LOG(LogTemp,Warning,TEXT("Found Location Failed"));
	return EBTNodeResult::Failed;
}
