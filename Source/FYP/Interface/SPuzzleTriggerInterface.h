// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SPuzzleTriggerInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class USPuzzleTriggerInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class FYP_API ISPuzzleTriggerInterface
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable,Category="Puzzle")
	void Unlock();
	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
};
