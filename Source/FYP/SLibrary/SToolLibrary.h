// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FYP/Enum/EMaterialParams.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SToolLibrary.generated.h"

/**
 * 
 */
class UMaterialInstanceDynamic;
UCLASS()
class FYP_API USToolLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable,Category="STool")
	static void ApplyMaterialParams(TMap<EMaterialParams, FVector3f> Params, UMaterialInstanceDynamic* MaterialInstanceDynamic);
};
