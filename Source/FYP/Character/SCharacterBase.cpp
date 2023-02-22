// Fill out your copyright notice in the Description page of Project Settings.


#include "./SCharacterBase.h"

#include "TimerManager.h"
#include "FYP/Component/SAttributeComponent.h"
#include "GameFramework/PawnMovementComponent.h"

// Sets default values
ASCharacterBase::ASCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AttributeComponent = CreateDefaultSubobject<USAttributeComponent>(TEXT("Attribute Component"));
}


// Called when the game starts or when spawned
void ASCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	FTimerHandle UnusedHandle;
	GetWorldTimerManager().SetTimer(UnusedHandle,FTimerDelegate::CreateWeakLambda(this,[this]
	{
		if(!IsValid(this)){return;}
		if(!this->GetMovementComponent()->IsFalling())
		{
			LastOnGroundLocation=GetActorLocation();
		};
	}),2,true,0);
}

FVector ASCharacterBase::GetLastOnGroundLocation() const
{
	return LastOnGroundLocation;
}

// Called every frame
void ASCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

// Called to bind functionality to input
void ASCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ASCharacterBase::Dead_Implementation()
{
}

void ASCharacterBase::Revived_Implementation()
{
}

FGenericTeamId ASCharacterBase::GetGenericTeamId() const
{
	return TeamID;
}




