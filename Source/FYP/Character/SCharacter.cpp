// Fill out your copyright notice in the Description page of Project Settings.


#include "SCharacter.h"

#include "Animation/AnimNode_LinkedAnimLayer.h"
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
}

// Called every frame
void ASCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ASCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("Move Forward / Backward",this,&ASCharacter::MoveForward);
	PlayerInputComponent->BindAxis("Move Right / Left",this,&ASCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn Right / Left Mouse",this,&APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("Look Up / Down Mouse",this,&APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Jump",EInputEvent::IE_Pressed,this,&ACharacter::Jump);
}

void ASCharacter::MoveForward(float val)
{
	FRotator ControlRot=GetControlRotation();
	ControlRot.Pitch=0;
	ControlRot.Roll=0;
	AddMovementInput(ControlRot.Vector(),val);
}
void ASCharacter::MoveRight(float val)
{
	FRotator ControlRot=GetControlRotation();
	ControlRot.Pitch=0;
	ControlRot.Roll=0;
	
	FVector ControlRightVec=UKismetMathLibrary::GetRightVector(ControlRot);
	AddMovementInput(ControlRightVec,val);
}
