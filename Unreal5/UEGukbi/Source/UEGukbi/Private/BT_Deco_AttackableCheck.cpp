// Fill out your copyright notice in the Description page of Project Settings.


#include "BT_Deco_AttackableCheck.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "MyAIController.h"

#include "MyPlayer.h"
#include "MyMonster.h"

bool UBT_Deco_AttackableCheck::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool result = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	if (result == false)
		return result;

	auto curPawn = Cast<AMyMonster>(OwnerComp.GetAIOwner()->GetPawn());
	auto player = Cast<AMyPlayer>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(FName(TEXT("Player"))));

	if (!curPawn->IsValidLowLevel() || !player->IsValidLowLevel())
		return false;


	float distance = player->GetDistanceTo(curPawn);

	if (distance < curPawn->AttackRange())
		return true;

	return false;
}
