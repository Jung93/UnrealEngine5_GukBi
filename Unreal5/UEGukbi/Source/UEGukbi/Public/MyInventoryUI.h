// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyItem.h"
#include "Components/TextBlock.h"
#include "MyInventoryUI.generated.h"

/**
 * 
 */
UCLASS()
class UEGUKBI_API UMyInventoryUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual bool Initialize() override;

	void SetItem_Index(int32 index, FMyItemInfo info);
	void DropItem(int32 index);
	void UseItem(int32 index);

	UFUNCTION()
	void SetTextBlock();

	void InitCurIndex() { _curIndex = -1; }


	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UUniformGridPanel* Grid;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* Drop;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* Use;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* ItemInfoText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<class UImage*> _slotImages;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<class UButton*> _slotBtns;


	UPROPERTY()
	UTexture2D* _defaultTexture;
	UPROPERTY()
	UTexture2D* _potionTexture;
	UPROPERTY()
	UTexture2D* _buffTexture;

	UPROPERTY()
	class UMyInventoryComponent* _inventoryComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UUniformGridPanel* InfoGrid;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UImage* _infoImage;

	int32 _curIndex = -1;

};
