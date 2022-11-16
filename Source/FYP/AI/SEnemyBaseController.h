// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AISenseConfig_Sight.h"
#include "SEnemyBaseController.generated.h"

/**
 * 
 */
UCLASS()
class FYP_API ASEnemyBaseController : public AAIController
{
	GENERATED_BODY()
public:
	ASEnemyBaseController();
	UFUNCTION()
	void OnPerception(AActor* Actor, FAIStimulus Stimulus);
	//virtual void OnPossess(APawn * InPawn) override;
	virtual void BeginPlay() override;
private:
	UPROPERTY(EditAnywhere,Category="Setting")
	UBehaviorTree* SEnemyBase_BT;

	UPROPERTY(VisibleAnywhere)
	UAIPerceptionComponent* AIPerceptionComponent;

	UPROPERTY(VisibleAnywhere)
	UAISenseConfig_Sight* SightConfig;
	
};
