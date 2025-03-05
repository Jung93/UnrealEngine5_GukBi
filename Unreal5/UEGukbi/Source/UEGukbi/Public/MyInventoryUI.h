// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyItem.h"
#include "MyInventoryUI.generated.h"

/**
 * 
 */
UCLASS()
class UEGUKBI_API UMyInventoryUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	void SetItem_Index(int32 index, FMyItemInfo info);
	void DropItem(int32 index);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UUniformGridPanel* Grid;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<class UImage*> _slotImages;

	UPROPERTY()
	UTexture2D* _potionTexture;

};
