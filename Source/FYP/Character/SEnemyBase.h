// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SCharacterBase.h"
#include "FYP/Interface/SAttackInterface.h"
#include "GameFramework/Character.h"
#include "SEnemyBase.generated.h"

UCLASS()
class FYP_API ASEnemyBase : public ASCharacterBase, public ISAttackInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASEnemyBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	bool CheckMontageIsPlaying(UAnimMontage* Montage) const;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Setting")
	UAnimMontage* AM_BasicAttack=nullptr;
};
