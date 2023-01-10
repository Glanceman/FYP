// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PlayMontageInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPlayMontageInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class FYP_API IPlayMontageInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintImplementableEvent,BlueprintCallable,Category="Montage")
	void StartAttackMontage(UAnimMontage* Montage);
	UFUNCTION(BlueprintImplementableEvent,BlueprintCallable,Category="Montage")
	void StopAttackMontage(bool condition,UAnimMontage* Montage);
	
};
