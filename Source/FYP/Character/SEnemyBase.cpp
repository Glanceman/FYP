// Fill out your copyright notice in the Description page of Project Settings.


#include "./SEnemyBase.h"
#include "Animation/AnimInstance.h"
#include "Components/SkeletalMeshComponent.h"

// Sets default values
ASEnemyBase::ASEnemyBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASEnemyBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

bool ASEnemyBase::CheckMontageIsPlaying(UAnimMontage* Montage) const
{
	const UAnimInstance* AnimInstance=GetMesh()->GetAnimInstance();
	if(!AnimInstance) return false;

	const bool result = AnimInstance->Montage_IsPlaying(Montage);
	return result;
}




