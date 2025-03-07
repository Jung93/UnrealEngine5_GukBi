// Fill out your copyright notice in the Description page of Project Settings.


#include "MyInventoryUI.h"
#include "Components/UniformGridPanel.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "Components/Border.h"
#include "MyInventoryComponent.h"
#include "MyButton.h"

bool UMyInventoryUI::Initialize()
{
	Super::Initialize();

	auto array = Grid->GetAllChildren();

	int index = 0;
	for (auto widget : array)
	{
		auto button = Cast<UMyButton>(widget);
		if (button)
		{
			button->OnClicked.AddDynamic(button, &UMyButton::SetCurIndex);
			button->OnClicked.AddDynamic(this, &UMyInventoryUI::SetTextBlock);
			button->widget = this;
			button->_curIndex = index;
			index++;

			auto image = Cast<UImage>(button->GetChildAt(0));
			if(image)
				_slotImages.Add(image);
		}

	}

	auto infoBorder = Cast<UBorder>(InfoGrid->GetChildAt(0));
	auto iamge = Cast<UImage>(infoBorder->GetChildAt(0));

	if (iamge)
	{
		_infoImage = iamge;
	}

	_defaultTexture = LoadObject<UTexture2D>(nullptr, TEXT("/Script/Engine.Texture2D'/Game/Graphics/UI/Items/Tex_Default.Tex_Default'"));
	_potionTexture = LoadObject<UTexture2D>(nullptr, TEXT("/Script/Engine.Texture2D'/Game/Graphics/UI/Items/Tex_seeds_06.Tex_seeds_06'"));
	_buffTexture = LoadObject<UTexture2D>(nullptr, TEXT("/Script/Engine.Texture2D'/Game/Graphics/UI/Items/Tex_gemstone_05.Tex_gemstone_05'"));


	return true;
}

void UMyInventoryUI::SetItem_Index(int32 index, FMyItemInfo info)
{
	if(info.itemId == 1 && info.type == FMyItemType::POTION)
		_slotImages[index]->SetBrushFromTexture(_potionTexture);
	if (info.itemId == 2 && info.type == FMyItemType::BUFF)
		_slotImages[index]->SetBrushFromTexture(_buffTexture);


}

void UMyInventoryUI::DropItem(int32 index)
{
	UTexture2D* dropItem = LoadObject<UTexture2D>(nullptr, TEXT("/Script/Engine.Texture2D'/Game/Graphics/UI/Items/Tex_Default.Tex_Default'"));

	_slotImages[index]->SetBrushFromTexture(dropItem);
	ItemInfoText->SetText(FText::FromString(TEXT("ItemType :  \nItemID : ")));
	_infoImage->SetBrushFromTexture(_defaultTexture);
}

void UMyInventoryUI::SetTextBlock()
{
	if (_inventoryComponent == nullptr)
		return;

	auto info = _inventoryComponent->GetItemInfoByIndex(_curIndex);

	if (info.itemId == 1 && info.type == FMyItemType::POTION)
	{
		ItemInfoText->SetText(FText::FromString(TEXT("ItemType : POTION \nItemID : 1")));
		_infoImage->SetBrushFromTexture(_potionTexture);
	}

	if (info.itemId == 2 && info.type == FMyItemType::BUFF)
	{
		ItemInfoText->SetText(FText::FromString(TEXT("ItemType : BUFF \nItemID : 2")));
		_infoImage->SetBrushFromTexture(_buffTexture);

	}

	if (info.itemId == -1 && info.type == FMyItemType::NONE)
	{
		ItemInfoText->SetText(FText::FromString(TEXT("ItemType :  \nItemID : ")));
		_infoImage->SetBrushFromTexture(_defaultTexture);

	}
}
