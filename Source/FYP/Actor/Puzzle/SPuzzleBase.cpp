// Fill out your copyright notice in the Description page of Project Settings.


#include "./SPuzzleBase.h"

// Sets default values
ASPuzzleBase::ASPuzzleBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ASPuzzleBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASPuzzleBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASPuzzleBase::Fail_Implementation()
{
}


void ASPuzzleBase::Succeed_Implementation()
{
}


void ASPuzzleBase::NotifyFromChildActor_Implementation(AActor* Child)
{
}


