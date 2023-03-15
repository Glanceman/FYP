// Fill out your copyright notice in the Description page of Project Settings.


#include "./SInteractiveWallBase.h"

// Sets default values
ASInteractiveWallBase::ASInteractiveWallBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ASInteractiveWallBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASInteractiveWallBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

