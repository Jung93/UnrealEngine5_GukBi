// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MyItem.h"
#include "MyInventoryComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(FItemAdd, int32, FMyItemInfo);

DECLARE_MULTICAST_DELEGATE_OneParam(FItemDrop, int32);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UEGUKBI_API UMyInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMyInventoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void AddItem(AMyItem* itemAddress);
	AMyItem* DropItem(class AMyPlayer* player);
	AMyItem* DropItem(int32 index, class AMyPlayer* player);

	FItemAdd itemAddEvent;
	FItemDrop itemDropEvent;

	FMyItemInfo GetItemInfoByIndex(int32 index);
	bool IsInventoryFull();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item", meta = (AllowPrivateAccess = "true"))
	TArray<AMyItem*> _items;
};
