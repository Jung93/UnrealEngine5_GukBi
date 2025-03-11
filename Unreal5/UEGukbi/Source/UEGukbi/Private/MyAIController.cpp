// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAIController.h"

#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NavigationSystem.h"

#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"


AMyAIController::AMyAIController()
{
}

void AMyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	//GetWorld()->GetTimerManager().SetTimer(_timerHandle, this, &AMyAIController::RandMove, 1.0f, true);

	UBlackboardComponent* temp = Blackboard;
	if (UseBlackboard(_blackBoard, temp))
	{
		if (RunBehaviorTree(_behaviorTree))
		{

		}
		else 
		{
			UE_LOG(LogTemp, Error, TEXT("BT failed"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("BB failed"));

	}
}

void AMyAIController::OnUnPossess()
{
	Super::OnUnPossess();

	//GetWorld()->GetTimerManager().ClearTimer(_timerHandle);
}

void AMyAIController::RandMove()
{
	auto curPawn = GetPawn();

	if (curPawn->IsValidLowLevel() == false)
		return;

	////현재 설정한  NavMesh 가져오는 것
	auto navMesh = UNavigationSystemV1::GetNavigationSystem(GetWorld());

	if (navMesh->IsValidLowLevel() == false)
		return;

	FNavLocation randLocation;

	if (navMesh->GetRandomPointInNavigableRadius(curPawn->GetActorLocation(), 500.0f, randLocation))
	{
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, randLocation.Location);
	}

}
