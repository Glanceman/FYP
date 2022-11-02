// Fill out your copyright notice in the Description page of Project Settings.


#include "./SKatanaBase.h"

#include "TimerManager.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/SkeletalMeshComponent.h"

ASKatanaBase::ASKatanaBase()
{
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);
	// Katana=CreateDefaultSubobject<UStaticMeshComponent>("Katana");
	// Katana->SetupAttachment(Root);
	// Katana->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Katana =CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Katana"));
	Katana->SetupAttachment(Root);
	
	Scabbard = CreateDefaultSubobject<UStaticMeshComponent>("Scabbard");
	Scabbard->SetupAttachment(Root);
	Scabbard->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}

TSubclassOf<ASBladeBase> ASKatanaBase::GetProjectileClass()
{
	return ProjectileBladeClass;
	
}

void ASKatanaBase::BeginPlay()
{
	Super::BeginPlay();

}



TArray<FVector> ASKatanaBase::GetTrackingPoints() const
{
	TArray<FVector> Points;
	const FVector Start= Katana->GetSocketLocation(TEXT("RangeStart"));
	const FVector End= Katana->GetSocketLocation(TEXT("RangeEnd"));
	const FRotator Rotation= UKismetMathLibrary::FindLookAtRotation(Start,End);
	for(int i=0; i<4;++i)
	{
		FVector temp=UKismetMathLibrary::GetForwardVector(Rotation)*25*i+Start;
		Points.Add(temp);
	}
	return Points;
}

void ASKatanaBase::AttackDetectionEvent()
{
	Prev_TrackingPoints=this->GetTrackingPoints();
	
	GetWorldTimerManager().SetTimer(TimerHandle,FTimerDelegate::CreateLambda([this]()
	{
		Curr_TrackingPoints=this->GetTrackingPoints();
		for(int i=0; i<Prev_TrackingPoints.Num();i++)
		{
			TArray<FHitResult> HitResult;
			GetWorld()->LineTraceMultiByChannel(HitResult,Prev_TrackingPoints[i],Curr_TrackingPoints[i],ECollisionChannel::ECC_Visibility);	
		}
		Prev_TrackingPoints=Curr_TrackingPoints;
	}),0.01,true);
}




