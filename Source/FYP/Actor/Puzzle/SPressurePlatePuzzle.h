// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SPuzzleBase.h"
#include "GameFramework/Actor.h"
#include "SPressurePlatePuzzle.generated.h"

class ASPressurePlate;
class UBoxComponent;
UCLASS()
class FYP_API ASPressurePlatePuzzle : public ASPuzzleBase
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASPressurePlatePuzzle();
	void AddNumberOfPressedPlates();
	void MinusNumberOfPressedPlates();
	virtual void NotifyFromChildActor_Implementation(AActor* Child) override;
	virtual void Fail_Implementation() override;
	virtual void Succeed_Implementation() override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;
	UFUNCTION()
	void OnGroundColliderOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(BlueprintReadOnly,EditAnywhere,Category="Setting")
	int32 Rows=1;
	UPROPERTY(BlueprintReadOnly,EditAnywhere,Category="Setting")
	int32 Cols=1;
	UPROPERTY(BlueprintReadOnly,EditAnywhere,Category="Setting")
	int32 Spacing=100;
	UPROPERTY(BlueprintReadOnly,EditAnywhere,Category="Setting")
	TSubclassOf<ASPressurePlate> PlateClass;
	UPROPERTY()
	TArray<ASPressurePlate*> Plates;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="Setting")
	UBoxComponent* BoxComponent;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="Setting")
	USceneComponent* DefaultSceneRoot;

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="Setting")
	TSet<FName> ExcludedPlate;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="Setting")
	FVector CheckGroundColliderSize{32,32,32};
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="Setting")
	AActor* TriggerableActor;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="Debug Section")
	int32 NumberOfChildActors=0;
	
private:
	UPROPERTY(BlueprintReadOnly,VisibleAnywhere,Category="Debug Section",meta=(AllowPrivateAccess = "true"))
	int32 NumberOfPlates;
	UPROPERTY(BlueprintReadOnly,VisibleAnywhere,Category="Debug Section",meta=(AllowPrivateAccess = "true"))
	int32 NumberOfPressed;
};
