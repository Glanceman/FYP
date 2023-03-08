// Fill out your copyright notice in the Description page of Project Settings.



#include "./SPressurePlate.h"
#include "SPressurePlatePuzzle.h"
#include "TimerManager.h"
#include "Components/BoxComponent.h"
#include "FYP/Character/SCharacter.h"
#include "FYP/SLibrary/SToolLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Materials/MaterialInstanceDynamic.h"

// Sets default values
ASPressurePlate::ASPressurePlate()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	BoxComponent= CreateDefaultSubobject<UBoxComponent>("Collider");
	RootComponent = BoxComponent;
	Plate = CreateDefaultSubobject<UStaticMeshComponent>("Plate");
	Plate -> SetupAttachment(BoxComponent);
	BoxComponent->OnComponentBeginOverlap.AddUniqueDynamic(this,&ASPressurePlate::OnOverlapBegin);
	BoxComponent->OnComponentEndOverlap.AddUniqueDynamic(this,&ASPressurePlate::OnEndOverlap);


}

// Called when the game starts or when spawned
void ASPressurePlate::BeginPlay()
{
	Super::BeginPlay();
	
	if(PuzzleParent==nullptr)
	{//get parent which create this by child component actor 
		PuzzleParent = Cast<ASPuzzleBase>(GetParentActor());
	}
	
}

void ASPressurePlate::OnConstruction(const FTransform& Transform)
{

	Super::OnConstruction(Transform);
	FVector Origin,BoxExtent;
	GetActorBounds(false,Origin,BoxExtent,false);
	BoxExtent.Z=BoxComponent->GetUnscaledBoxExtent().Z;
	BoxComponent->SetBoxExtent(BoxExtent+ColliderSizeOffset);
	if(Plate->GetMaterial(0)->IsA(UMaterialInstanceDynamic::StaticClass()))
	{
		//UE_LOG(LogTemp, Warning, TEXT("Plate material is already a UMaterialInstanceDynamic"));
		MaterialInstanceDynamic = Cast<UMaterialInstanceDynamic>(Plate->GetMaterial(0));
	}else
	{
		MaterialInterface = Plate->GetMaterial(0);
		MaterialInstanceDynamic = UMaterialInstanceDynamic::Create(MaterialInterface,this);
		
	}
	Plate->SetMaterial(0,MaterialInstanceDynamic);
	//MaterialInstanceDynamic->SetVectorParameterValue(MaterialSlotName,OriginalColor);
	USToolLibrary::ApplyMaterialParams(InitParams,MaterialInstanceDynamic);
}

void ASPressurePlate::Reset_Implementation()
{
	bOn=false;
	MaterialInstanceDynamic->SetVectorParameterValue(MaterialSlotName,OriginalColor);
}

void ASPressurePlate::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                     UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(PuzzleParent==nullptr)
	{
		if (bDebug) UE_LOG(LogTemp, Warning, TEXT("PuzzleParent is not set"));
		return;
	}
	if(PuzzleParent->bSolved==true) return;
	if (bDebug) UE_LOG(LogTemp, Warning, TEXT("Actor: %s"),*OtherActor->GetName());
	if(OtherActor)
	{
		if(bOn==false)
		{
			//play sound
			if(IsValid(ReactCue))
			{
				UGameplayStatics::PlaySoundAtLocation(GetWorld(),ReactCue,GetActorLocation(),GetActorRotation(),1,1,0);
			}
			//MaterialInstanceDynamic->SetVectorParameterValue(MaterialSlotName,TargetColor);
			USToolLibrary::ApplyMaterialParams(TargetParams,MaterialInstanceDynamic);
			bOn=true;
			PuzzleParent->NotifyFromChildActor(this);
		}else
		{
			//PuzzleParent->MinusNumberOfPressedPlates();
			//MaterialInstanceDynamic->SetVectorParameterValue(MaterialSlotName,OriginalColor);
			USToolLibrary::ApplyMaterialParams(InitParams,MaterialInstanceDynamic);
			bOn=false;
			PuzzleParent->NotifyFromChildActor(this);
		}	
	}
}

void ASPressurePlate::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(bOnlyTriggerByEnter){return;}
	if(!IsValid(PuzzleParent))
	{
		if (bDebug) UE_LOG(LogTemp, Warning, TEXT("PuzzleParent is not set"));
		return;
	}
	if(PuzzleParent->bSolved==true) return;
	if(OtherActor)
	{
		if(bOn==true)
		{
			//MaterialInstanceDynamic->SetVectorParameterValue(MaterialSlotName,OriginalColor);
			USToolLibrary::ApplyMaterialParams(InitParams,MaterialInstanceDynamic);
			bOn=false;
			PuzzleParent->NotifyFromChildActor(this);
		}	
	}
	
}

void ASPressurePlate::SetParentLater(AActor* Parent)
{
	PuzzleParent = Cast<ASPuzzleBase>(Parent);
	if(IsValid(PuzzleParent)==false)
	{
		if (bDebug) UE_LOG(LogTemp, Warning, TEXT("Set PuzzleParent Later Fail"));
	}

}


// Called every frame
void ASPressurePlate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



