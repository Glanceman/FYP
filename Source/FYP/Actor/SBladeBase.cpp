// Fill out your copyright notice in the Description page of Project Settings.


#include "./SBladeBase.h"

// Sets default values
ASBladeBase::ASBladeBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ProjectileMovementComponent=CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");
	ProjectileMovementComponent->SetAutoActivate(false);

}

// Called when the game starts or when spawned
void ASBladeBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASBladeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

