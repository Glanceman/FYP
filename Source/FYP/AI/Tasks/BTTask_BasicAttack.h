// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_BasicAttack.generated.h"

/**
 * 
 */
UCLASS()
class FYP_API UBTTask_BasicAttack : public UBTTaskNode
{
	GENERATED_BODY()
public:
		UBTTask_BasicAttack();
	
private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
