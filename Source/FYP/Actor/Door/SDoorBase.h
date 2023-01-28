// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SDoorBase.generated.h"

UCLASS()
class FYP_API ASDoorBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASDoorBase();
	UFUNCTION(BlueprintImplementableEvent,BlueprintCallable,Category="Interaction")
	void Open(float DeltaTime);
	UFUNCTION(BlueprintImplementableEvent,BlueprintCallable,Category="Interaction")
	void Close(float DeltaTime);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



};
