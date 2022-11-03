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
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void MoveRightEvent(float val);
	void JumpEvent();
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//functions
	void MoveForwardEvent(float val);
	void DashPressEvent();
	UFUNCTION(BlueprintCallable)
	ASKatanaBase* GetWeapon() const;
	void SwapAnimationClass();
	UFUNCTION(BlueprintCallable)
	bool GetIsDash() const;
	UFUNCTION(BlueprintCallable)
	bool GetIsSprint()const;

	UFUNCTION(BlueprintCallable)
	void AttachWeapon();
	UFUNCTION(BlueprintCallable)
	void DetachWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



private:
	//functions
	UFUNCTION()
	void UpdateDash();
	UFUNCTION()
	void Run();
	void DashReleaseEvent();
	//variable

	UPROPERTY(EditAnywhere)
	USpringArmComponent* CameraBoom;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<ASKatanaBase> WeaponClass;
	
	UPROPERTY()
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

	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess=true),Category="Character Setting")
	bool bAllowBasicMovement=true;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,meta=(AllowPrivateAccess=true),Category="Character Setting")
	float WalkMaxSpeed=500;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,meta=(AllowPrivateAccess=true),Category="Character Setting")
	float RunMaxSpeed=1000;
};
