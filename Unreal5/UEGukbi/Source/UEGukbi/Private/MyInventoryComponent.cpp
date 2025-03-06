// Fill out your copyright notice in the Description page of Project Settings.


#include "MyInventoryComponent.h"
#include "MyPlayer.h"

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

void UMyInventoryComponent::AddItem(AMyItem* itemAddress, int32 itemID, FMyItemType type)
{
	FMyItemInfo addIteminfo;
	addIteminfo.item = itemAddress;
	addIteminfo.itemId = itemID;
	addIteminfo.type = type;

	FMyItemInfo temp;
	auto target = _items.FindByPredicate([temp](const FMyItemInfo info)->bool
		{
			if (info.itemId == temp.itemId && info.type == temp.type)
				return true;
			return false;
		});

	if (target == nullptr)
		return;

	*target = addIteminfo;

	int32 targetIndex = 0;

	int64 temp1 = (int64)target;
	int64 temp2 = (int64)(&_items[0]);
	targetIndex = (temp1 - temp2) / sizeof(FMyItemInfo);

	itemAddEvent.Broadcast(targetIndex, *target);
}

FMyItemInfo UMyInventoryComponent::DropItem(AMyPlayer* player)
{
	FMyItemInfo result;

	auto targetIndex = _items.FindLastByPredicate([](const FMyItemInfo info)-> bool
		{
			if (info.itemId == -1 && info.type == FMyItemType::NONE)
				return false;
			return true;
		});

	if (targetIndex == INDEX_NONE)
		return FMyItemInfo();

	result = _items[targetIndex];

	_items[targetIndex].item->SetActorHiddenInGame(false);
	_items[targetIndex].item->SetActorEnableCollision(true);

	FVector location = player->GetLocation();
	FVector randomLocation = FVector(FMath::RandRange(-100.0f, 200.0f), FMath::RandRange(-250.0f, 200.0f), 0.0f);

	_items[targetIndex].item->SetActorLocation(location + randomLocation);


	_items[targetIndex] = FMyItemInfo();
	itemDropEvent.Broadcast(targetIndex);


	return result;
}

FMyItemInfo UMyInventoryComponent::DropItem(int32 index)
{
	return FMyItemInfo();
}

bool UMyInventoryComponent::IsInventoryFull()
{
	FMyItemInfo temp;
	auto target = _items.FindByPredicate([temp](const FMyItemInfo info)->bool
		{
			if (info.itemId == temp.itemId && info.type == temp.type)
				return true;
			return false;
		});

	if (target == nullptr)
		return true;

	return false;
}

