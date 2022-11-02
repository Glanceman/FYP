// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "./SWeaponBase.h"
#include "SBladeBase.h"
#include "SKatanaBase.generated.h"

/**
 * 
 */
UCLASS()
class FYP_API ASKatanaBase : public ASWeaponBase
{
	GENERATED_BODY()
public:
	ASKatanaBase();
	UFUNCTION(BlueprintCallable)
	TSubclassOf<ASBladeBase> GetProjectileClass();

	// UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	// UStaticMeshComponent* Katana;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USkeletalMeshComponent* Katana;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	UStaticMeshComponent* Scabbard;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
private:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;
	UPROPERTY(EditAnywhere)
	TSubclassOf<ASBladeBase> ProjectileBladeClass;
	UPROPERTY()
	TArray<FVector> Prev_TrackingPoints;
	UPROPERTY()
	TArray<FVector> Curr_TrackingPoints;
	UPROPERTY()
	FTimerHandle TimerHandle;

	
	UFUNCTION(BlueprintCallable)
	TArray<FVector> GetTrackingPoints() const;
	UFUNCTION(BlueprintCallable)
	void AttackDetectionEvent();
	
};
