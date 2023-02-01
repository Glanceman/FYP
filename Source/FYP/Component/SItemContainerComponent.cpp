// Fill out your copyright notice in the Description page of Project Settings.


#include "./SItemContainerComponent.h"

// Sets default values for this component's properties
USItemContainerComponent::USItemContainerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void USItemContainerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USItemContainerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void USItemContainerComponent::CollectItem(FName ItemName)
{
	if(ItemsName.Contains(ItemName))
	{
		ItemsName[ItemName]++;
	}else
	{
		ItemsName.Add(ItemName,1);
	};
}

