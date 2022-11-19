// Fill out your copyright notice in the Description page of Project Settings.


#include "./BTTask_ClearBlackBoardValue.h"

#include "BehaviorTree/BlackboardComponent.h"

UBTTask_ClearBlackBoardValue::UBTTask_ClearBlackBoardValue()
{
	NodeName=TEXT("ClearBlackBloadValue");
}

EBTNodeResult::Type UBTTask_ClearBlackBoardValue::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const FName KeyName=GetSelectedBlackboardKey();
	UBlackboardComponent* BlackboardComponent=OwnerComp.GetBlackboardComponent();
	BlackboardComponent->ClearValue(KeyName);
	return EBTNodeResult::Succeeded;	
}
