// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayer.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

#include "MyAnimInstance.h"
#include "MyStatComponent.h"

#include "MyItem.h"
#include "Blueprint/UserWidget.h"
#include "MyInventoryUI.h"
#include "MyInventoryComponent.h"

AMyPlayer::AMyPlayer()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//blueprint에서 skeletalMesh
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));

	_springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	_camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	//상속관계 설정
	_springArm->SetupAttachment(GetCapsuleComponent());
	_camera->SetupAttachment(_springArm);

	_springArm->TargetArmLength = 500.0f;
	_springArm->SetRelativeRotation(FRotator(-35.0f, 0.0f, 0.0f));

	//inventory
	static ConstructorHelpers::FClassFinder<UMyInventoryUI> inventoryClass(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/BluePrints/BP_MyInventory.BP_MyInventory_C'"));
	if (inventoryClass.Succeeded())
	{
		_inventoryWidget = CreateWidget<UUserWidget>(GetWorld(), inventoryClass.Class);
	}
	
	_inventoryComponent = CreateDefaultSubobject<UMyInventoryComponent>(TEXT("InventoryComponent"));

}

void AMyPlayer::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	auto inventoryUI = Cast<UMyInventoryUI>(_inventoryWidget);
	if (inventoryUI)
	{
		_inventoryComponent->itemAddEvent.AddUObject(inventoryUI, &UMyInventoryUI::SetItem_Index);
		_inventoryComponent->itemDropEvent.AddUObject(inventoryUI, &UMyInventoryUI::DropItem);
	}
}

void AMyPlayer::BeginPlay()
{
	Super::BeginPlay();

	if (_inventoryWidget)
		_inventoryWidget->AddToViewport();


}

void AMyPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

void AMyPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* enhancedInputCompnent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (enhancedInputCompnent)
	{
		enhancedInputCompnent->BindAction(_moveAction, ETriggerEvent::Triggered, this, &AMyPlayer::Move);
		enhancedInputCompnent->BindAction(_lookAction, ETriggerEvent::Triggered, this, &AMyPlayer::Look);
		enhancedInputCompnent->BindAction(_jumpAction, ETriggerEvent::Triggered, this, &AMyPlayer::Jump);
		enhancedInputCompnent->BindAction(_attackAction, ETriggerEvent::Triggered, this, &AMyPlayer::Attack);
		enhancedInputCompnent->BindAction(_itemAction, ETriggerEvent::Triggered, this, &AMyPlayer::DropItem);
	}

}


void AMyPlayer::Move(const FInputActionValue& value)
{
	if (_isAttack)
		return;
	FVector2D moveVector = value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		if (moveVector.Length() > 0.01f)
		{
			FVector forWard = GetActorForwardVector();
			FVector right = GetActorRightVector();

			_vertical = moveVector.Y;
			_horizontal = moveVector.X;

			AddMovementInput(forWard, moveVector.Y * _statComponent->GetSpeed());
			AddMovementInput(right, moveVector.X * _statComponent->GetSpeed());
		}
	}
}

void AMyPlayer::Look(const FInputActionValue& value)
{
	FVector2D lookAxisVector = value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(lookAxisVector.X);
		AddControllerPitchInput(-lookAxisVector.Y);
	}
}

void AMyPlayer::Attack(const FInputActionValue& value)
{
	if (_isAttack)
		return;

	bool isPress = value.Get<bool>();

	if (isPress)
	{
		_isAttack = true;

		_curAttackSection = (_curAttackSection) % 2 + 1;

		_animInstance->PlayAnimMontage();
		_animInstance->JumpToSection(_curAttackSection);
	}
}

void AMyPlayer::DropItem(const FInputActionValue& value)
{
	if (_isAttack)
		return;

	bool isPress = value.Get<bool>();

	if (isPress && _inventoryComponent)
	{
		auto itemInfo = _inventoryComponent->DropItem(this);




		UE_LOG(LogTemp, Error, TEXT("ID : %d"), itemInfo.itemId);
	}

}


bool AMyPlayer::AddItem(AMyItem* item)
{
	if (item && _inventoryComponent)
	{
		if (!_inventoryComponent->IsInventoryFull())
		{
			auto info = item->GetItemInfo();
			_inventoryComponent->AddItem(info.item, info.itemId, info.type);
			return true;
		}
	}

	return false;
	//_items.Add(item);
	//UE_LOG(LogTemp, Log, TEXT("Items count : %d"), _items.Num());
}
