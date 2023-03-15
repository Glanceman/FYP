// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FYP/Interface/SInteractInterface.h"
#include "GameFramework/Actor.h"
#include "SInteractiveWallBase.generated.h"

UCLASS()
class FYP_API ASInteractiveWallBase : public AActor, public ISInteractInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASInteractiveWallBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
