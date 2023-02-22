// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "./SWeaponBase.h"
#include "SBladeBase.h"
#include "SKatanaBase.generated.h"

class UAnimMontage;
/**
 * 
 */

UCLASS()
class FYP_API ASKatanaBase : public ASWeaponBase
{
	GENERATED_BODY()
public:
	ASKatanaBase();
	
	// UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	// UStaticMeshComponent* Katana;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,Category="Setting")
	USkeletalMeshComponent* Katana;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Setting")
		UStaticMeshComponent* Scabbard;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
		UAnimMontage* AttackMontage;
	UFUNCTION(BlueprintCallable)
		TSubclassOf<ASBladeBase> GetProjectileClass();
	UFUNCTION(BlueprintCallable)
		void AttackDetectionEvent();
	UFUNCTION(BlueprintCallable)
		void StopDetectionEvent();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UFUNCTION(BlueprintCallable)
	TArray<FVector> GetTrackingPoints() const;
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;
	UPROPERTY(EditAnywhere,Category="Setting")
	TSubclassOf<ASBladeBase> ProjectileBladeClass;
	UPROPERTY()
	TArray<FVector> Prev_TrackingPoints;
	UPROPERTY()
	TArray<FVector> Curr_TrackingPoints;
	UPROPERTY()
	FTimerHandle TimerHandle;
	UPROPERTY()
	float TimerHandleSinceTriggerDuration=0;
	UPROPERTY(EditAnywhere,Category="Debug Section")
	bool bDebug=false;
	UPROPERTY()
	TSet<AActor*> HitActors;
	
	
};
