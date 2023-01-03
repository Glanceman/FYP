// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SMathLibrary.generated.h"

/**
 * 
 */
UCLASS()
class FYP_API USMathLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category="STool")
	static float SignedAngleBetweenTwoVectors(FVector v1, FVector v2);
};
