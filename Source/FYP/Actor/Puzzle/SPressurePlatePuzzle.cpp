// Fill out your copyright notice in the Description page of Project Settings.


#include "./SPressurePlatePuzzle.h"
#include "SPressurePlate.h"
#include "TimerManager.h"
#include "Components/BoxComponent.h"
#include "FYP/Character/SCharacter.h"
#include "FYP/Interface/SPuzzleTriggerInterface.h"
// Sets default values
ASPressurePlatePuzzle::ASPressurePlatePuzzle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	DefaultSceneRoot=CreateDefaultSubobject<USceneComponent>("Default Root");
	RootComponent=DefaultSceneRoot;
	BoxComponent= CreateDefaultSubobject<UBoxComponent>("Collider");
	BoxComponent->SetupAttachment(RootComponent);
}



// Called when the game starts or when spawned
void ASPressurePlatePuzzle::BeginPlay()
{
	Super::BeginPlay();

}

void ASPressurePlatePuzzle::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	
	if(!IsValid(PlateClass))
	{
		if(bDebug) UE_LOG(LogTemp, Warning, TEXT("PlateClass is not set"));
		return;
	}
	int32 counter=0;
	for(int R=0; R<Rows;R++)
	{
		for(int C=0; C<Cols;C++)
		{
			FVector RelativeLocation(0,0,0);
			RelativeLocation.X=Spacing*R;
			RelativeLocation.Y=Spacing*C;
			FName ExcludedKey =FName(*FString::FromInt(int(R*10+C)));
			
			if(ExcludedKey.IsValid() && ExcludedPlate.Find(ExcludedKey))
			{
				if(bDebug) UE_LOG(LogTemp, Warning, TEXT(" Key %s"), *ExcludedKey.ToString());
				//spawn box collision
				UBoxComponent* CheckGroundCollider = NewObject<UBoxComponent>(this);
				CheckGroundCollider->CreationMethod=EComponentCreationMethod::SimpleConstructionScript;
				CheckGroundCollider->AttachToComponent(RootComponent,FAttachmentTransformRules::KeepRelativeTransform);
				CheckGroundCollider->SetRelativeLocation(RelativeLocation);
				CheckGroundCollider->SetBoxExtent(CheckGroundColliderSize);
				CheckGroundCollider->OnComponentBeginOverlap.AddDynamic(this,&ASPressurePlatePuzzle::OnGroundColliderOverlapBegin);
			}else
			{ //spawn plate actor
				if(UChildActorComponent* ChildActorComponent=NewObject<UChildActorComponent>(this))
				{
					ChildActorComponent->SetChildActorClass(PlateClass);
					//ChildActorComponent->RegisterComponent();
					ChildActorComponent->CreationMethod=EComponentCreationMethod::SimpleConstructionScript;
					ChildActorComponent->AttachToComponent(RootComponent,FAttachmentTransformRules::KeepRelativeTransform);
					ChildActorComponent->SetRelativeLocation(RelativeLocation);
					//ChildActorComponent->OnComponentCreated();
					ChildActorComponent->CreateChildActor();
					counter++;
				}	
			}
		}
	}
	NumberOfPlates=counter;
	FVector Origin, BoxExtent;
	GetActorBounds(true,Origin,BoxExtent,true);
	BoxExtent.Z=BoxComponent->GetUnscaledBoxExtent().Z;
	BoxComponent->SetBoxExtent(BoxExtent);
	BoxComponent->SetWorldLocation(Origin);
	if(bDebug)
	{
		TArray<AActor*>Actors;
		GetAllChildActors(Actors);
		NumberOfChildActors=Actors.Num();	
	}
}

void ASPressurePlatePuzzle::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);
	if(bDebug) UE_LOG(LogTemp, Warning, TEXT("Puzzle End Overlap"));
	if(bSolved==true)return;
	if(Cast<ASCharacter>(OtherActor))
	{
		if( NumberOfPlates == NumberOfPressed)
		{
			Succeed();	
		}else
		{
			Fail();
		}
	}
}

void ASPressurePlatePuzzle::OnGroundColliderOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(bSolved){return;}
	if(Cast<ASCharacter>(OtherActor)) Fail();
}

void ASPressurePlatePuzzle::Succeed()
{
	if(bDebug) UE_LOG(LogTemp, Warning, TEXT("Solved"));
	bSolved=true;
	if(IsValid(TriggerableActor) && Cast<ISPuzzleTriggerInterface>(TriggerableActor))
	{
		ISPuzzleTriggerInterface::Execute_TriggerToUnlock(TriggerableActor);
	}else
	{
		if(bDebug) UE_LOG(LogTemp, Warning, TEXT("TriggerableActor is not valid"));
	}
}

void ASPressurePlatePuzzle::Fail()
{
	if(bDebug) UE_LOG(LogTemp, Warning, TEXT("Fail"));
	FTimerHandle UnusedHandle;
	GetWorldTimerManager().SetTimer(UnusedHandle,FTimerDelegate::CreateLambda([this]
	{
		this->NumberOfPressed=0;
		TArray<AActor*> Actors;
		this->GetAllChildActors(Actors,false);
		for (AActor* Actor : Actors)
		{
			ASPressurePlate* Plate = Cast<ASPressurePlate>(Actor);
			if(Plate)
			{
				Plate->Reset_Implementation();
			}else
			{
				break;
			}
		} 
		
	}),1,false);
	
}
void ASPressurePlatePuzzle::AddNumberOfPressedPlates()
{
	NumberOfPressed++;
	if( NumberOfPlates == NumberOfPressed) Succeed();
}
void ASPressurePlatePuzzle::MinusNumberOfPressedPlates()
{
	NumberOfPressed--;
	Fail();
}

// Called every frame
void ASPressurePlatePuzzle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

