// Fill out your copyright notice in the Description page of Project Settings.


#include "MyMonster.h"
#include "MyItem.h"
#include "Components/WidgetComponent.h"
#include "MyHpBar.h"
#include "MyStatComponent.h"
#include "MyAnimInstance.h"
#include "Kismet/KismetMathLibrary.h"
#include "MyPlayerController.h"
#include "MyPlayer.h"

AMyMonster::AMyMonster()
{
	PrimaryActorTick.bCanEverTick = true;

	_hpBarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HpBar"));
	_hpBarWidget->SetupAttachment(GetMesh());
	_hpBarWidget->SetWidgetSpace(EWidgetSpace::World);

	static ConstructorHelpers::FClassFinder<UMyHpBar> hpBarClass(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/BluePrints/BP_MyHpbar.BP_MyHpbar_C'"));
	if (hpBarClass.Succeeded())
	{
		_hpBarWidget->SetWidgetClass(hpBarClass.Class);
	}
}



void AMyMonster::BeginPlay()
{
	Super::BeginPlay();

	auto hpBar = Cast<UMyHpBar>(_hpBarWidget->GetWidget());
	if (hpBar)
	{
		_statComponent->_hpChanged.AddUObject(hpBar, &UMyHpBar::SetHpBarValue);
	}

	//_animInstance->_deadEvent.AddUObject(this, &AMyMonster::SpawnItem);

}

void AMyMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto playerCameraManager = GetWorld()->GetFirstPlayerController()->PlayerCameraManager;

	if (playerCameraManager)
	{
		FVector hpBarLocation = _hpBarWidget->GetComponentLocation();
		FVector cameraLocation = playerCameraManager->GetCameraLocation();
		FRotator rot = UKismetMathLibrary::FindLookAtRotation(hpBarLocation, cameraLocation);
		_hpBarWidget->SetWorldRotation(rot);
	}

}

void AMyMonster::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float AMyMonster::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	_statComponent->AddCurHp(-Damage);

	auto attackerController = Cast<APlayerController>(EventInstigator);

	if (attackerController)
	{
		// Player...
		if (IsDead())
		{
			UE_LOG(LogTemp, Error, TEXT("Be Dead by Player"));

			auto player = Cast<AMyCharacter>(DamageCauser);

			if (player)
			{
				player->AddExp(_monsterExp);
			}
		}
	}

	return Damage;
}

//void AMyMonster::SpawnItem()
//{
//
//	FVector SpawnLocation = FVector(FMath::RandRange(-100.0f, 200.0f), FMath::RandRange(-250.0f, 200.0f), 40.0f);
//	FRotator SpawnRotation = FRotator::ZeroRotator;
//
//	auto SpawnedItem = GetWorld()->SpawnActor<AMyItem>(_item, SpawnLocation, SpawnRotation);
//	if (!SpawnedItem)
//	{
//		UE_LOG(LogTemp, Error, TEXT("SpawnActor failure: _item couldn't create AMyItem"));
//	}
//	else
//	{
//		UE_LOG(LogTemp, Warning, TEXT("_item!"));
//	}
//}


