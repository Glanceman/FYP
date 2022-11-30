// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTS_CheckAttackRange.generated.h"

/**
 * 
 */
UCLASS()
class FYP_API UBTS_CheckAttackRange : public UBTService
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere,Category="AI")
	int32 AttackRange = 100;
	UPROPERTY(EditAnywhere,Category="AI")
	FBlackboardKeySelector bAttackRangeKey;
	UPROPERTY(EditAnywhere,Category="AI")
	FBlackboardKeySelector TargetActorKey;
	
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
