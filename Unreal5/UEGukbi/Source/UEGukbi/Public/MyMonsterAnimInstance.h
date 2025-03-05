// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MyMonsterAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class UEGUKBI_API UMyMonsterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	

public:
	UMyMonsterAnimInstance();


private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pawn", meta = (AllowPrivateAccess = "true"))
	bool _isDead = false;

};
