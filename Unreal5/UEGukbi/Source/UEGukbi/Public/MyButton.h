// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "MyButton.generated.h"

/**
 * 
 */
UCLASS()
class UEGUKBI_API UMyButton : public UButton
{
	GENERATED_BODY()
	
public:
	virtual void PostLoad() override;

	UFUNCTION()
	void SetCurIndex();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UMyInventoryUI* widget;

	int32 _curIndex;
};
