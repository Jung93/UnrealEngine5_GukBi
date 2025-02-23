// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyTutoPawn.generated.h"

class UInputAction;
struct FInputActionValue;

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

	UFUNCTION(BlueprintCallable)
	void Temp();

	void Move(const FInputActionValue& value);

private:
	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	UStaticMeshComponent* _mesh;

	UPROPERTY(EditAnywhere, Category = "Speed")
	float _moveSpeed = 2.0f;
	UPROPERTY(EditAnywhere, Category = "Speed")
	float _rotationSpeed = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* _moveAction;

};
