// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyTutoPawn.generated.h"

//1. 언리얼의 이벤트 함수 실행 순서


UCLASS()
class UEGUKBI_API AMyTutoPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyTutoPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY()
	UStaticMeshComponent* _mesh;


	float _moveSpeed = 2.0f;
	float _rotationSpeed = 100.0f;


};
