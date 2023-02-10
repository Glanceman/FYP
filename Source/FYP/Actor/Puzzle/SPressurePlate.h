// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SPressurePlate.generated.h"

class ASPressurePlatePuzzle;
class UBoxComponent;
class UMaterialInstanceDynamic;
UCLASS()
class FYP_API ASPressurePlate : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASPressurePlate();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform) override;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Reset() override;
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="Setting")
	UStaticMeshComponent* Plate;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="Setting")
	UBoxComponent* BoxComponent;
	UPROPERTY(BlueprintReadWrite,Category="Setting")
	UMaterialInterface* MaterialInterface;
	UPROPERTY(BlueprintReadWrite,Category="Setting")
	UMaterialInstanceDynamic* MaterialInstanceDynamic;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="Setting")
	FName MaterialSlotName="Color";
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="Setting")
	FLinearColor OriginalColor;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="Setting")
	FLinearColor TargetColor;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="Setting")
	bool bOn=false;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="Setting")
	TSubclassOf<ASPressurePlatePuzzle> PuzzleClass;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="Setting")
	ASPressurePlatePuzzle* PuzzleParent;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="Setting")
	FVector ColliderSizeOffset{32,32,0};
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="Setting")
	bool bDebug=true;
};
