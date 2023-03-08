// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class FYP_API ASGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable,Category="GameMode")
	void StartGame();
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable,Category="GameMode")
	void PauseGame();
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable,Category="GameMode")
	void BackToMain();
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable,Category="GameMode")
    void Quit();
	
};
