// Fill out your copyright notice in the Description page of Project Settings.


#include "MyInventoryComponent.h"
#include "MyPlayer.h"
#include "MyItem.h"

// Sets default values for this component's properties
UMyInventoryComponent::UMyInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	_items.SetNum(9);
}


// Called when the game starts
void UMyInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UMyInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UMyInventoryComponent::AddItem(AMyItem* itemAddress)
{
	auto target = _items.FindByPredicate([](AMyItem* item)->bool
		{
			if (item == nullptr)
				return true;
			return false;
		});

	if (target == nullptr)
		return;

	*target = itemAddress;

	int32 targetIndex = 0;

	int64 temp1 = (int64)target;
	int64 temp2 = (int64)(&_items[0]);
	targetIndex = (temp1 - temp2) / sizeof(int64);

	itemAddEvent.Broadcast(targetIndex, itemAddress->GetItemInfo());
}

AMyItem* UMyInventoryComponent::DropItem()
{

	auto targetIndex = _items.FindLastByPredicate([](AMyItem* item)-> bool
		{
			if (item == nullptr)
				return false;
			return true;
		});

	if (targetIndex == INDEX_NONE)
		return nullptr;


	AMyItem* dropItem = _items[targetIndex];

	_items[targetIndex] = nullptr;

	return dropItem;
}

AMyItem* UMyInventoryComponent::DropItem(int32 index)
{
	if (index >= _items.Num() || index < 0)
		return nullptr;

	if (_items[index] == nullptr)
		return nullptr;

	AMyItem* dropItem = _items[index];


	_items[index] = nullptr;
	return dropItem;
}

AMyItem* UMyInventoryComponent::UseItem(int32 index)
{
	if (index >= _items.Num() || index < 0)
		return nullptr;

	if (_items[index] == nullptr)
		return nullptr;

	AMyItem* usedItem = _items[index];

	_items[index] = nullptr;
	return usedItem;
}

int32 UMyInventoryComponent::GetLastItemIndex()
{
	auto targetIndex = _items.FindLastByPredicate([](AMyItem* item)-> bool
		{
			if (item == nullptr)
				return false;
			return true;
		});

	if (targetIndex == INDEX_NONE)
		return 0;

	return targetIndex;
}

FMyItemInfo UMyInventoryComponent::GetItemInfoByIndex(int32 index)
{
	if (index < 0 || index >= _items.Num())
		return FMyItemInfo();

	if (_items[index] == nullptr)
		return FMyItemInfo();

	return _items[index]->GetItemInfo();

}

bool UMyInventoryComponent::IsInventoryFull()
{
	auto target = _items.FindByPredicate([](AMyItem* item)->bool
		{
			if (item == nullptr)
				return true;
			return false;
		});

	if (target == nullptr)
		return true;

	return false;
}

