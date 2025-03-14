// Fill out your copyright notice in the Description page of Project Settings.


#include "BT_Deco_DeathCheck.h"
#include "MyMonster.h"
#include "MyAIController.h"

bool UBT_Deco_DeathCheck::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool result = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	if(!result)
		return result;

	auto curPawn = Cast<AMyMonster>(OwnerComp.GetAIOwner()->GetPawn());

	if (!curPawn->IsValidLowLevel())
		return false;

	if (curPawn->IsDead())
		return false;

	return true;

}
