// Fill out your copyright notice in the Description page of Project Settings.


#include "./SKatanaBase.h"

#include "TimerManager.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/DamageType.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

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
	HitActors.Empty();
	//set up timer
	GetWorldTimerManager().SetTimer(TimerHandle,FTimerDelegate::CreateLambda([this]()
	{
		Curr_TrackingPoints=this->GetTrackingPoints();
		TArray<AActor*>IgnoredActor;
		IgnoredActor.Add(GetOwner());
		for(int i=0; i<Prev_TrackingPoints.Num();i++)
		{
			FHitResult HitResult;
			if(UKismetSystemLibrary::SphereTraceSingle(GetWorld(),Prev_TrackingPoints[i],Curr_TrackingPoints[i],10.0f,static_cast<ETraceTypeQuery>(ECollisionChannel::ECC_Visibility),false,IgnoredActor,EDrawDebugTrace::ForDuration,HitResult,true))
			//if(GetWorld()->LineTraceSingleByChannel(HitResult,Prev_TrackingPoints[i],Curr_TrackingPoints[i],ECollisionChannel::ECC_Visibility))
			{
				if(HitActors.Find(HitResult.GetActor())==nullptr)
				{
					const AActor* HitActor = HitResult.GetActor();

					// if(bDebug)
					// {
					//
					// 	UE_LOG(LogTemp, Display ,TEXT("Actor Name %s"),*HitResult.GetActor()->GetName());
					// }
					UGameplayStatics::ApplyDamage(HitResult.GetActor(),DamageValue,HitActor->GetInstigatorController(),this,UDamageType::StaticClass());
					HitActors.Add(HitResult.GetActor());
				}
			};
			//show debug lines
			if(bDebug)
			{
				DrawDebugLine(GetWorld(),Prev_TrackingPoints[i],Curr_TrackingPoints[i],FColor(255, 0, 0),false, 2, 0,2);
			}
			
		}
		Prev_TrackingPoints=Curr_TrackingPoints;
	}),0.01,true);
}

void ASKatanaBase::StopDetectionEvent()
{
	GetWorldTimerManager().ClearTimer(TimerHandle);
}




