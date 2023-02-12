// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FYP/Interface/SPuzzleTriggerInterface.h"
#include "GameFramework/Actor.h"
#include "SDoorBase.generated.h"

UCLASS()
class FYP_API ASDoorBase : public AActor, public ISPuzzleTriggerInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASDoorBase();
	UFUNCTION(BlueprintImplementableEvent,BlueprintCallable,Category="Interaction")
	void Open(float DeltaTime);
	UFUNCTION(BlueprintImplementableEvent,BlueprintCallable,Category="Interaction")
	void Close(float DeltaTime);

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="Setting")
	FName TriggerKeyName="Any";
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="Setting")
	bool bAutoClose=true;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;




};