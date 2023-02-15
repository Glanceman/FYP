// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "Components/TimelineComponent.h"
#include "SCharacterBase.h"
#include "Animation/AnimInstance.h"
#include "FYP/Interface/SAttackInterface.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "SCharacter.generated.h"

class ASKatanaBase;
class USItemContainerComponent;
UCLASS()
class FYP_API ASCharacter : public ASCharacterBase, public ISAttackInterface
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
	void SwapAnimationClass();
	UFUNCTION(BlueprintCallable)
		ASKatanaBase* GetWeapon() const;
	UFUNCTION(BlueprintCallable)
		bool GetIsDash() const;
	UFUNCTION(BlueprintCallable)
		bool GetIsSprint()const;
	UFUNCTION(BlueprintCallable)
		void AttachWeapon();
	UFUNCTION(BlueprintCallable)
		void DetachWeapon();
	
	UPROPERTY(BlueprintReadWrite)
	bool bAttack=false;
	UPROPERTY(BlueprintReadWrite)
	USItemContainerComponent* SItemContainerComponent;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="SCharacter Setting")
	bool bAllowBasicMovement=true;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="SCharacter Setting")
	float WalkMaxSpeed=500;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="SCharacter Setting")
	float RunMaxSpeed=1000;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="SCharacter Setting")
	bool bIsAttachWeapon =false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	//virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	UFUNCTION(BlueprintCallable)
	virtual void BasicAttack_Implementation() override;

private:
	//functions
	// UFUNCTION()
	// 	void UpdateDash();
	// UFUNCTION()
	// 	void Run();
	UFUNCTION()
	void DashReleaseEvent();
	UFUNCTION()
		void AttackRotate();
	float StartYaw;;
	float TargetYaw;
	//variables
	UPROPERTY(EditAnywhere)
		USpringArmComponent* CameraBoom;
	
	UPROPERTY(EditAnywhere)
		TSubclassOf<ASKatanaBase> WeaponClass;
	
	UPROPERTY()
		ASKatanaBase* Weapon=nullptr;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,meta=(AllowPrivateAccess=true))
		UCameraComponent* Camera;
	
	UPROPERTY(EditAnywhere,Category="Animation Setting")
		UAnimMontage* EquipWeaponMontage;
	
	UPROPERTY(EditAnywhere,Category="Animation Setting")
		UAnimMontage* DetachWeaponMontage;
	
	UPROPERTY(EditAnywhere,Category="Animation Setting")
		TSubclassOf<UAnimInstance> WeaponAnimClass;
	
	UPROPERTY(EditAnywhere,Category="Animation Setting")
		TSubclassOf<UAnimInstance> DefaultAnimClass;

	UPROPERTY()
		FTimeline DashTimeLine;
	UPROPERTY()
		FTimeline AttackOrientationTimeLine;
	
	UPROPERTY(EditAnywhere,Category="Time Line Setting")
		UCurveFloat* DashCurveFloat;
	UPROPERTY(EditAnywhere,Category="Time Line Setting")
		UCurveFloat* OrientationSpeedCurveFloat;
	
	UPROPERTY()
		bool bIsDash=false;
	
	UPROPERTY()
		bool bIsSprint=false;
	
	UPROPERTY()
		bool bDashKeyHold=false;
	



	
};
