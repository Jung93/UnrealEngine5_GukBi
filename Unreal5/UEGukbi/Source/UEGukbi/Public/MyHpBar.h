// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyHpBar.generated.h"

/**
 * 
 */
UCLASS()
class UEGUKBI_API UMyHpBar : public UUserWidget
{
	GENERATED_BODY()
	
public:

	void SetHpBarValue(float ratio);

	virtual void NativeTick(const FGeometry& MyGeometry, float InDelataTime) override;


private:
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* PB_HpBar;//에디터의 위젯블루프린트와 이름을 일치시켜야함

};
