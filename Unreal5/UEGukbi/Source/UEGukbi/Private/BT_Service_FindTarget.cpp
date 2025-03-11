// Fill out your copyright notice in the Description page of Project Settings.


#include "BT_Service_FindTarget.h"
#include "MyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BehaviorTree.h"

#include "MyPlayer.h"
#include "DrawDebugHelpers.h"
#include "Engine/OverlapResult.h"

void UBT_Service_FindTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	auto curPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (curPawn->IsValidLowLevel() == false)
		return;

	FVector pos = curPawn->GetActorLocation();
	float sphereRaidus = 700.0f;

	TArray<FOverlapResult> overlapResults;
	FCollisionQueryParams qParams(NAME_None, false, curPawn);

	bool result = GetWorld()->OverlapMultiByChannel(
		overlapResults,
		pos,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel12,
		FCollisionShape::MakeSphere(sphereRaidus),
		qParams
	);

	DrawDebugSphere(GetWorld(), pos, sphereRaidus, 30, FColor::Green, false, 0.3f);


	if (!result)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(FName(TEXT("Player")), nullptr);// 감지가 안되어있으니 BlackBoard에서 해제


		return;
	}
	else
	{
		for (auto& overlapResult : overlapResults)
		{
			auto player = Cast<AMyPlayer>(overlapResult.GetActor());

			if (player->IsValidLowLevel()== true)
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsObject(FName(TEXT("Player")), player);// 감지가 안되어있으니 BlackBoard에서 해제
				DrawDebugSphere(GetWorld(), pos, sphereRaidus, 30, FColor::Red, false, 0.3f);

				//FRotator rot = (player->GetActorLocation() - curPawn->GetActorLocation()).GetSafeNormal().Rotation();
				//curPawn->SetActorRotation(FMath::RInterpTo());

				return;
			}
		}

	}
}
