// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "FYP/Interface/PlayMontageInterface.h"
#include "SAnimCharacterBase.generated.h"

/**
 * 
 */
UCLASS()
class FYP_API USAnimCharacterBase : public UAnimInstance, public IPlayMontageInterface
{
	GENERATED_BODY()
	
};
