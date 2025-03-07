// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayer.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

#include "MyPlayerController.h"
#include "MyAnimInstance.h"
#include "MyStatComponent.h"

#include "MyItem.h"
#include "Blueprint/UserWidget.h"
#include "MyInventoryUI.h"
#include "MyInventoryComponent.h"

#include "Components/Button.h"

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
		inventoryUI->_inventoryComponent = _inventoryComponent;
		_inventoryComponent->itemAddEvent.AddUObject(inventoryUI, &UMyInventoryUI::SetItem_Index);
		_inventoryComponent->itemDropEvent.AddUObject(inventoryUI, &UMyInventoryUI::DropItem);
		inventoryUI->Drop->OnClicked.AddDynamic(this, &AMyPlayer::Drop);
	}
}

void AMyPlayer::BeginPlay()
{
	Super::BeginPlay();


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
		enhancedInputCompnent->BindAction(_inventoryAction, ETriggerEvent::Triggered, this, &AMyPlayer::OpenInventory);
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

	}

}

void AMyPlayer::OpenInventory(const FInputActionValue& value)
{
	bool isPress = value.Get<bool>();

	if (isPress)
	{
		auto controller = Cast<AMyPlayerController>(GetController());
		if (_isInventoryOpen)
		{
			if(controller)
				controller->HideUI();
			_inventoryWidget->RemoveFromViewport();
		}
		else
		{
			if (controller)
				controller->ShowUI();
			_inventoryWidget->AddToViewport();
		}

		_isInventoryOpen = !_isInventoryOpen;

	}
}


bool AMyPlayer::AddItem(AMyItem* item)
{
	if (item && _inventoryComponent)
	{
		if (!_inventoryComponent->IsInventoryFull())
		{
			_inventoryComponent->AddItem(item);
			return true;
		}
	}

	return false;
}

void AMyPlayer::Drop()
{

	int32 curDropIndex = -1;
	auto invenUI = Cast<UMyInventoryUI>(_inventoryWidget);
	if (invenUI)
		curDropIndex = invenUI->_curIndex;

	_inventoryComponent->DropItem(curDropIndex, this);
	invenUI->_curIndex = -1;
}
