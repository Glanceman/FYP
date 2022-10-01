// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "Components/TimelineComponent.h"

#include "FYP/Actor/SKatanaBase.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "SCharacter.generated.h"

UCLASS()
class FYP_API ASCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void MoveRight(float val);
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//functions
	void MoveForward(float val);
	void DashAndRun();
	UFUNCTION(BlueprintCallable)
	ASKatanaBase* GetWeapon() const;
	void SwapAnimationClass();
	UFUNCTION(BlueprintCallable)
	bool GetIsDash() const;
	UFUNCTION(BlueprintCallable)
	bool GetIsSprint()const;
private:
	//functions
	UFUNCTION()
	void UpdateDash();
	UFUNCTION()
	void Run();
	void RecoverFromDash();
	//variable
	FOnTimelineFloatStatic DashTimeLineUpdateDelegate;
	FOnTimelineEventStatic DashTimeLineFinishedDelegate;
	UPROPERTY(EditAnywhere)
	USpringArmComponent* CameraBoom;
	UPROPERTY(EditAnywhere)
	TSubclassOf<ASKatanaBase> WeaponClass;
	UPROPERTY(EditAnywhere)
	ASKatanaBase* Weapon=nullptr;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,meta=(AllowPrivateAccess=true))
	UCameraComponent* Camera;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess=true))
	bool bIsAttachWeapon =false;
	UPROPERTY(EditAnywhere,Category="Anim Montage")
	UAnimMontage* EquipWeaponMontage;
	UPROPERTY(EditAnywhere,Category="Anim Montage")
	UAnimMontage* DetachWeaponMontage;
	UPROPERTY(EditAnywhere,Category="Anim")
	TSubclassOf<UAnimInstance> WeaponAnimClass;
	UPROPERTY(EditAnywhere,Category="Anim")
	TSubclassOf<UAnimInstance> DefaultAnimClass;
	UPROPERTY()
	FTimeline DashTimeLine;
	UPROPERTY(EditAnywhere,Category="Time Line Setting")
	UCurveFloat* DashCurveFloat;
	UPROPERTY()
	bool bIsDash=false;
	UPROPERTY()
	bool bIsSprint=false;
	UPROPERTY()
	bool bDashKeyHold=false;

};
