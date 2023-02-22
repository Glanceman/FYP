// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SPuzzleBase.generated.h"

UCLASS()
class FYP_API ASPuzzleBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASPuzzleBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable,Category="SPuzzleBase")
	void Fail();
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable,Category="SPuzzleBase")
	void Succeed();

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable,Category="SPuzzleBase")
	void NotifyFromChildActor(AActor* Child);

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="Setting")
	bool bDebug=true;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="Setting")
	bool bSolved=false;

};
