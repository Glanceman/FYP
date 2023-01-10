// Fill out your copyright notice in the Description page of Project Settings.


#include "./BTTask_BasicAttack.h"

#include "AIController.h"
#include "FYP/Character/SEnemyBase.h"

UBTTask_BasicAttack::UBTTask_BasicAttack()
{
	NodeName=TEXT("Basic Attack");
}

EBTNodeResult::Type UBTTask_BasicAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const AAIController* AIController = OwnerComp.GetAIOwner();
	if(ensure(AIController))
	{
		const APawn* Pawn = AIController->GetPawn();
		if(!ensure(Pawn)) return EBTNodeResult::Failed;

		ASEnemyBase* Character = (ASEnemyBase*)Pawn;
		if(!Character) return EBTNodeResult::Failed;
		const ISAttackInterface* AttackInterface= Cast<ISAttackInterface>(Pawn);
		if(ensureMsgf(AttackInterface,TEXT("The AI does not equip attack interface")))
		{
			ISAttackInterface::Execute_BasicAttack(Character);
		}else
		{
			return EBTNodeResult::Failed;
		}
		// bool bAttacking=Character->CheckMontageIsPlaying(Character->AM_BasicAttack);
		// if(bAttacking)
		// {
		// 	return EBTNodeResult::InProgress;
		// }
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}
