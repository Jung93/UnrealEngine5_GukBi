// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BT_Service_FindTarget.generated.h"

/*
Service
- 주기적으로 체크
 주기적으로 Player가 몬스터와 가까이 있는지 체크하고 BlackBoard의 Player 키에 기입
 
 */
UCLASS()
class UEGUKBI_API UBT_Service_FindTarget : public UBTService
{
	GENERATED_BODY()
	
public:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
