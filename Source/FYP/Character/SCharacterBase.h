// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GenericTeamAgentInterface.h"
#include "SCharacterBase.generated.h"

class USAttributeComponent;

UCLASS()
class FYP_API ASCharacterBase : public ACharacter, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASCharacterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	


	virtual FGenericTeamId GetGenericTeamId() const override;


	UPROPERTY(VisibleAnywhere,BlueprintReadOnly);
	USAttributeComponent* AttributeComponent;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Setting")
	FGenericTeamId ClassId=0;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Setting")
	float BasicDamageValue = 1;
};
