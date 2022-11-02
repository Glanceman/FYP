// Fill out your copyright notice in the Description page of Project Settings.


#include "./SEnemyBaseController.h"

void ASEnemyBaseController::BeginPlay()
{
	Super::BeginPlay();
	if(SEnemyBase_BT==nullptr)
	{
		UE_LOG(LogTemp,Warning,TEXT("No behavior tree for ASEnemyBaseController"));
		return;
	}
	RunBehaviorTree(SEnemyBase_BT);
}
