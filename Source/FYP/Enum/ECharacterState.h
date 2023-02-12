// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ECharacterState.generated.h"
/**
 * & "and" used check whether has the flag
 *  | "or" used to add the flag
 *  &"and",~"not" used to remove the flag
 */ 
UENUM(BlueprintType, Meta=(Bitflags))
enum class ECharacterState : uint8
{
	NONE = 0 UMETA(Hidden),
	Alive =1 UMETA(Displayname = "Alive"),
	Dead = 2 UMETA(Displayname = "Dead"), //4 , 8
};

