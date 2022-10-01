// Fill out your copyright notice in the Description page of Project Settings.


#include "./SKatanaBase.h"

ASKatanaBase::ASKatanaBase()
{
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);
	Katana=CreateDefaultSubobject<UStaticMeshComponent>("Katana");
	Katana->SetupAttachment(Root);
	Katana->SetCollisionEnabled(ECollisionEnabled::NoCollision);

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




