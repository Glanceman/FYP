// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "SEnemyBaseController.generated.h"

/**
 * 
 */
UCLASS()
class FYP_API ASEnemyBaseController : public AAIController
{
	GENERATED_BODY()
public:
	//virtual void OnPossess(APawn * InPawn) override;
	virtual void BeginPlay() override;
private:
	UPROPERTY(EditAnywhere,Category="Setting")
	UBehaviorTree* SEnemyBase_BT;
	
};
