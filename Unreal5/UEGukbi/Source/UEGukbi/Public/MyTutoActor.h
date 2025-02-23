// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyTutoActor.generated.h"

//UCLASS ��� ����
//1. �޸� ����(shared_ptr)
//2. ���÷���(reflection)
UCLASS() //UObject�� ��ӹ޴� Ŭ����
class UEGUKBI_API AMyTutoActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyTutoActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY()
	UStaticMeshComponent* _mesh;
	float _rotationSpeed = -10.0f;
	float _moveSpeed = 10.0;

	//actor�� ���忡 �����Ϸ��� transform�� �־���Ѵ�
	//1. mesh�� �־���Ѵ�
	//2. material�� �־���Ѵ�
	//3. transform(4X4���)



};
