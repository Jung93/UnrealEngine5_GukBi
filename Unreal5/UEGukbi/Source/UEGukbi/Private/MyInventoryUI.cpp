// Fill out your copyright notice in the Description page of Project Settings.


#include "MyInventoryUI.h"
#include "Components/UniformGridPanel.h"
#include "Components/Image.h"

void UMyInventoryUI::NativeConstruct()
{
	Super::NativeConstruct();

	auto array = Grid->GetAllChildren();

	for (auto widget : array)
	{
		auto image = Cast<UImage>(widget);
		if (image)
		{
			_slotImages.Add(image);
		}

	}

	UE_LOG(LogTemp, Error, TEXT("Image Size : %d"), _slotImages.Num());

	_potionTexture = LoadObject<UTexture2D>(nullptr, TEXT("/Script/Engine.Texture2D'/Game/Graphics/UI/Items/Tex_seeds_06_b.Tex_seeds_06_b'"));
}

void UMyInventoryUI::SetItem_Index(int32 index, FMyItemInfo info)
{
	int a = index;
	if(info.itemId == 1 && info.type == FMyItemType::POTION)
		_slotImages[index]->SetBrushFromTexture(_potionTexture);

}

void UMyInventoryUI::DropItem(int32 index)
{
	UTexture2D* dropItem = LoadObject<UTexture2D>(nullptr, TEXT("/Script/Engine.Texture2D'/Game/Graphics/UI/Items/Tex_Default.Tex_Default'"));

	_slotImages[index]->SetBrushFromTexture(dropItem);


}
