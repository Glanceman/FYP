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
	virtual FGenericTeamId GetGenericTeamId() const override;
	
	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;
	UPROPERTY(BlueprintReadWrite,VisibleAnywhere,Category="Setting")
	FGenericTeamId TeamID;
private:
	UPROPERTY(EditAnywhere,Category="Setting")
	UBehaviorTree* SEnemyBase_BT;

	UPROPERTY(VisibleAnywhere)
	UAIPerceptionComponent* AIPerceptionComponent;

	// UPROPERTY(VisibleAnywhere)
	// UAISenseConfig_Sight* SightConfig;
	// UPROPERTY(EditDefaultsOnly,Category="SightConfig")
	// float SightRadius=1000;
	// UPROPERTY(EditDefaultsOnly,Category="SightConfig")
	// float LoseSightRadius=2000;
	// UPROPERTY(EditDefaultsOnly,Category="SightConfig")
	// float PeripheralVisionAngleDegrees=60;
	// UPROPERTY(EditDefaultsOnly,Category="SightConfig")
	// bool bCheckEnemy=true;
	// UPROPERTY(EditDefaultsOnly,Category="SightConfig")
	// bool bCheckNeutral=true;
	// UPROPERTY(EditDefaultsOnly,Category="SightConfig")
	// bool bCheckFriend=true;


};
