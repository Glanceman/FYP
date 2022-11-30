﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "SCharacter.h"

#include "Animation/AnimNode_LinkedAnimLayer.h"
#include "Components/InputComponent.h"
#include "Curves/CurveFloat.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values
ASCharacter::ASCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>("Camera Boom");
	CameraBoom->SetupAttachment(RootComponent);
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(CameraBoom);
	bUseControllerRotationYaw=false;
	CameraBoom->bUsePawnControlRotation=true;
	GetCharacterMovement()->bOrientRotationToMovement=true;
	

}

// Called when the game starts or when spawned
void ASCharacter::BeginPlay()
{
	Super::BeginPlay();
	Weapon = GetWorld()->SpawnActor<ASKatanaBase>(WeaponClass);
	Weapon->Katana->AttachToComponent(GetMesh(),FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("DEF-Katana_Target"));
	Weapon->Scabbard->AttachToComponent(GetMesh(),FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("DEF-Scabbard_Target"));
	//Weapon->Katana->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Weapon->SetOwner(this);
	GetMesh()->LinkAnimClassLayers(DefaultAnimClass);

	//set TimeLine
	FOnTimelineFloatStatic DashTimeLineUpdateDelegate;
	DashTimeLineUpdateDelegate.BindUFunction(this,"UpdateDash");
	DashTimeLine.AddInterpFloat(DashCurveFloat,DashTimeLineUpdateDelegate);
	FOnTimelineEventStatic DashTimeLineFinishedDelegate;
	DashTimeLineFinishedDelegate.BindUFunction(this,"Run");
	DashTimeLine.SetTimelineFinishedFunc(DashTimeLineFinishedDelegate);
	DashTimeLine.SetTimelineLength(DashTimeLength+0.01f);
	DashTimeLine.SetLooping(false);
}

// Called every frame
void ASCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	DashTimeLine.TickTimeline(DeltaTime);
}

// Called to bind functionality to input
void ASCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("Move Forward / Backward",this,&ASCharacter::MoveForwardEvent);
	PlayerInputComponent->BindAxis("Move Right / Left",this,&ASCharacter::MoveRightEvent);
	PlayerInputComponent->BindAxis("Turn Right / Left Mouse",this,&APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("Look Up / Down Mouse",this,&APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Jump",EInputEvent::IE_Pressed,this,&ASCharacter::JumpEvent);
	PlayerInputComponent->BindAction("EquipWeapon",EInputEvent::IE_Pressed,this,&ASCharacter::SwapAnimationClass);
	
	PlayerInputComponent->BindAction("Dash",EInputEvent::IE_Pressed,this,&ASCharacter::DashPressEvent);
	PlayerInputComponent->BindAction("Dash",EInputEvent::IE_Released,this,&ASCharacter::DashReleaseEvent);

}

void ASCharacter::MoveForwardEvent(float val)
{
	if(!bAllowBasicMovement)return;
	FRotator ControlRot=GetControlRotation();
	ControlRot.Pitch=0;
	ControlRot.Roll=0;
	AddMovementInput(ControlRot.Vector(),val);
}

void ASCharacter::MoveRightEvent(float val)
{
	if(!bAllowBasicMovement)return;
	FRotator ControlRot=GetControlRotation();
	ControlRot.Pitch=0;
	ControlRot.Roll=0;

	const FVector ControlRightVec=UKismetMathLibrary::GetRightVector(ControlRot);
	AddMovementInput(ControlRightVec,val);
}
void ASCharacter::JumpEvent()
{
	if(!bAllowBasicMovement)return;
	Jump();
}

ASKatanaBase* ASCharacter::GetWeapon() const
{
	return Weapon;
}

void ASCharacter::SwapAnimationClass()
{
	bIsAttachWeapon=!bIsAttachWeapon;
	if(bIsAttachWeapon)
	{
		PlayAnimMontage(EquipWeaponMontage);

	}else
	{
		PlayAnimMontage(DetachWeaponMontage);
	}
}

bool ASCharacter::GetIsDash() const
{
	return bIsDash;
}

bool ASCharacter::GetIsSprint() const
{
	return bIsSprint;
}

void ASCharacter::AttachWeapon()
{
	if(Weapon==nullptr){return;}
	Weapon->Katana->AttachToComponent(GetMesh(),FAttachmentTransformRules::KeepRelativeTransform,"DEF-weapon_R");
	GetMesh()->LinkAnimClassLayers(WeaponAnimClass);
	bIsAttachWeapon=true;
}

void ASCharacter::DetachWeapon()
{
	if(Weapon==nullptr){return;}
	Weapon->Katana->AttachToComponent(GetMesh(),FAttachmentTransformRules::KeepRelativeTransform,"DEF-Katana_Target");
	GetMesh()->LinkAnimClassLayers(DefaultAnimClass);
	bIsAttachWeapon=false;
}

void ASCharacter::DashPressEvent()
{

	if(DashCurveFloat==nullptr)
	{
		return;
	}
	
	bDashKeyHold=true;
	GetCharacterMovement()->MaxWalkSpeed=3000;
	GetCharacterMovement()->MaxAcceleration=3000;
	bIsDash=true;
	
	DashTimeLine.PlayFromStart();
}

void ASCharacter::UpdateDash()
{

	if(DashTimeLine.GetPlaybackPosition()<=DashTimeLength)
	{
		AddMovementInput(GetActorForwardVector());
		const float CurveFloat = DashCurveFloat->GetFloatValue(DashTimeLine.GetPlaybackPosition());
		const float FOV = FMath::Lerp(90,100,CurveFloat);
		Camera->SetFieldOfView(FOV);	
	}
}

void ASCharacter::Run()
{
	bIsDash=false;
	const FVector CharacterCurrentAcceleration = GetCharacterMovement()->GetCurrentAcceleration();
	if(bDashKeyHold && !(CharacterCurrentAcceleration.Length()==0))
	{
		GetCharacterMovement()->MaxWalkSpeed=RunMaxSpeed;
		bIsSprint=true;
		
	}else
	{
		bIsSprint=false;
		GetCharacterMovement()->MaxWalkSpeed=WalkMaxSpeed;
			
	}
	GetCharacterMovement()->MaxAcceleration=1000;;
	//UE_LOG(LogTemp,Warning,TEXT("Finish Called %f %b"),GetCharacterMovement()->GetCurrentAcceleration().Length(),bIsDash);
}

void ASCharacter::DashReleaseEvent()
{
	bDashKeyHold=false;
	if(bIsSprint)
	{
		bIsSprint=false;
		GetCharacterMovement()->MaxWalkSpeed=WalkMaxSpeed;
	}
}



