// Fill out your copyright notice in the Description page of Project Settings.


#include "SCharacter.h"
#include "FYP/Actor/SKatanaBase.h"

#include "Components/InputComponent.h"
#include "Curves/CurveFloat.h"
#include "FYP/Component/SItemContainerComponent.h"
#include "FYP/Interface/PlayMontageInterface.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"


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

	SItemContainerComponent = CreateDefaultSubobject<USItemContainerComponent>("ItemContainerComponent");

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



}

void ASCharacter::BasicAttack_Implementation() 
{
	ISAttackInterface::BasicAttack_Implementation();
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	const FVector CameraWorldLocation = Camera->GetComponentLocation();
	const FVector CameraForwardVector = Camera->GetForwardVector();
	TArray<AActor*>IgnoredActor;
	IgnoredActor.Add(GetController()->GetPawn());
	TArray<FHitResult> HitResults;
	UKismetSystemLibrary::SphereTraceMulti(GetWorld(),CameraWorldLocation,CameraWorldLocation+(CameraForwardVector*1000),100,static_cast<ETraceTypeQuery>(ECollisionChannel::ECC_Visibility),false,IgnoredActor,EDrawDebugTrace::ForDuration,HitResults,true);
	StartYaw=GetActorRotation().Yaw;
	TargetYaw=Camera->GetComponentRotation().Yaw;
	for(int i=0; i<HitResults.Num();i++)
	{
		AActor* HitActor= HitResults[i].GetActor();
		if(Cast<ASCharacterBase>(HitActor))
		{
			DrawDebugSphere(GetWorld(),HitActor->GetActorLocation(),80.0f,10,FColor::Blue,true, -1, 0, 1);
			FRotator Rotation=UKismetMathLibrary::FindLookAtRotation(GetActorLocation(),HitActor->GetActorLocation());
			TargetYaw=Rotation.Yaw;
			break;
		}
	}

	if(Cast<IPlayMontageInterface>(AnimInstance))
	{
		IPlayMontageInterface::Execute_StartAttackMontage(AnimInstance,Weapon->AttackMontage);
		FOnTimelineFloatStatic TimeLineUpdateDelegate;
		TimeLineUpdateDelegate.BindUFunction(this,TEXT("AttackRotate"));
		AttackOrientationTimeLine.AddInterpFloat(OrientationSpeedCurveFloat,TimeLineUpdateDelegate);
		AttackOrientationTimeLine.SetLooping(false);
		float min, max;
		OrientationSpeedCurveFloat->GetTimeRange(min,max);
		float length=max-min;
		AttackOrientationTimeLine.SetTimelineLength(length);
		AttackOrientationTimeLine.PlayFromStart();
	};
}

void ASCharacter::AttackRotate()
{
	float Alpha =OrientationSpeedCurveFloat->GetFloatValue(AttackOrientationTimeLine.GetPlaybackPosition());
	FRotator Rotator(0,StartYaw,0);
	FRotator Rotator2(0,TargetYaw,0);
	FRotator NewRotator=FMath::Lerp(Rotator,Rotator2,Alpha);
	SetActorRotation(NewRotator);	
}

// Called every frame
void ASCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	DashTimeLine.TickTimeline(DeltaTime);
	AttackOrientationTimeLine.TickTimeline(DeltaTime);
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
	
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	IPlayMontageInterface* MontageInterface= Cast<IPlayMontageInterface>(AnimInstance);
	if(!MontageInterface){return;}
	bool Condition = bAttack==false && GetCharacterMovement()->GetCurrentAcceleration().Length()!=0;
	IPlayMontageInterface::Execute_StopAttackMontage(AnimInstance,Condition,Weapon->AttackMontage);
	
	FRotator ControlRot=GetControlRotation();
	ControlRot.Pitch=0;
	ControlRot.Roll=0;
	AddMovementInput(ControlRot.Vector(),val);
}

void ASCharacter::MoveRightEvent(float val)
{
	if(!bAllowBasicMovement)return;

	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	IPlayMontageInterface* MontageInterface= Cast<IPlayMontageInterface>(AnimInstance);
	if(!MontageInterface){return;}
	bool Condition = bAttack==false && GetCharacterMovement()->GetCurrentAcceleration().Length()!=0;
	IPlayMontageInterface::Execute_StopAttackMontage(AnimInstance,Condition,Weapon->AttackMontage);
	
	FRotator ControlRot=GetControlRotation();
	ControlRot.Pitch=0;
	ControlRot.Roll=0;

	const FVector ControlRightVec=UKismetMathLibrary::GetRightVector(ControlRot);
	AddMovementInput(ControlRightVec,val);
}
void ASCharacter::JumpEvent()
{
	if(!bAllowBasicMovement)return;
	
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	IPlayMontageInterface* MontageInterface= Cast<IPlayMontageInterface>(AnimInstance);
	if(!MontageInterface){return;}
	bool Condition = bAttack==false && GetCharacterMovement()->GetCurrentAcceleration().Length()!=0;
	IPlayMontageInterface::Execute_StopAttackMontage(AnimInstance,Condition,Weapon->AttackMontage);
	
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

	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	IPlayMontageInterface* MontageInterface= Cast<IPlayMontageInterface>(AnimInstance);
	if(!MontageInterface){return;}
	bool Condition = bAttack==false && GetCharacterMovement()->GetCurrentAcceleration().Length()!=0;
	IPlayMontageInterface::Execute_StopAttackMontage(AnimInstance,Condition,Weapon->AttackMontage);
	
	GetCharacterMovement()->MaxWalkSpeed=3000;
	GetCharacterMovement()->MaxAcceleration=3000;
	bIsDash=true;
	//set TimeLine
	float min, max;
	DashCurveFloat->GetTimeRange(min,max);
	float length = max - min; 
	FOnTimelineFloatStatic DashTimeLineUpdateDelegate;
	DashTimeLineUpdateDelegate.BindUFunction(this,"UpdateDash");
	DashTimeLine.AddInterpFloat(DashCurveFloat,DashTimeLineUpdateDelegate);
	FOnTimelineEventStatic DashTimeLineFinishedDelegate;
	DashTimeLineFinishedDelegate.BindUFunction(this,"Run");
	DashTimeLine.SetTimelineFinishedFunc(DashTimeLineFinishedDelegate);

	DashTimeLine.SetTimelineLength(length+0.01f);
	DashTimeLine.SetLooping(false);
	
	DashTimeLine.PlayFromStart();
}

void ASCharacter::UpdateDash()
{
	float min, max;
	DashCurveFloat->GetTimeRange(min,max);
	if(DashTimeLine.GetPlaybackPosition()<=max)
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



