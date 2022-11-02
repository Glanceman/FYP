// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_AssignPatrolLocation.generated.h"

/**
 * 
 */
UCLASS()
class FYP_API UBTTask_AssignPatrolLocation : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTTask_AssignPatrolLocation();
	UPROPERTY(EditAnywhere,Category="Setting")
	float Radius=300;

private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
