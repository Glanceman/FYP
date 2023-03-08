// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EMaterialParams.generated.h"
/**
 * 
 */

UENUM(BlueprintType, Meta=(Bitflags))
enum class EMaterialParams :uint8
{
	NONE = 0 UMETA(Hidden),
	BaseColor =1 UMETA(Displayname = "BaseColor"),
	Roughness = 2 UMETA(Displayname = "Roughness"), //4 , 8
	EmissionStrength =4 UMETA(Displayname = "EmissionStrength")
};
