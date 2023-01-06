// Fill out your copyright notice in the Description page of Project Settings.


#include "./BTS_CheckAttackRange.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

void UBTS_CheckAttackRange::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	UBlackboardComponent* BlackboardComponent=OwnerComp.GetBlackboardComponent();
	if(ensure(BlackboardComponent))
	{
		AActor* TargetActor=Cast<AActor>(BlackboardComponent->GetValueAsObject(TargetActorKey.SelectedKeyName));
		if(TargetActor)
		{
			const AAIController* AIController = OwnerComp.GetAIOwner();
			if(ensure(AIController))
			{
				const APawn* Pawn = AIController->GetPawn();
				if(ensure(Pawn))
				{
					const float Distance = FVector::Dist(TargetActor->GetActorLocation(),Pawn->GetActorLocation());
					const bool bWithinRange= Distance <= AttackRange? true : false ;
					BlackboardComponent->SetValueAsBool(bAttackRangeKey.SelectedKeyName,bWithinRange);
				}
			}
		}
	}
}
