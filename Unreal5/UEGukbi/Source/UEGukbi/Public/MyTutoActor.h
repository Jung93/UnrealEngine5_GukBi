// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyTutoActor.generated.h"

//UCLASS 사용 이유
//1. 메모리 관리(shared_ptr)
//2. 리플렉션(reflection)
UCLASS() //UObject를 상속받는 클래스
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

	//actor가 월드에 존재하려면 transform이 있어야한다
	//1. mesh가 있어야한다
	//2. material이 있어야한다
	//3. transform(4X4행렬)



};
