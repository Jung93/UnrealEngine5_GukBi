// Fill out your copyright notice in the Description page of Project Settings.


#include "MyItem.h"

#include "Components/CapsuleComponent.h"
#include "MyCharacter.h"
#include "MyPlayer.h"
#include "MyPlayerController.h"

// Sets default values
AMyItem::AMyItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	_collider = CreateDefaultSubobject<UCapsuleComponent>("Collider");
	_mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");

	_mesh->SetupAttachment(_collider);

	RootComponent = _collider;

}

void AMyItem::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	_collider->OnComponentBeginOverlap.AddDynamic(this, &AMyItem::OnMyCharacterOverlap);
	_collider->OnComponentEndOverlap.AddDynamic(this, &AMyItem::OnMyCharacterOverlapEnd);
}

// Called when the game starts or when spawned
void AMyItem::BeginPlay()
{
	Super::BeginPlay();

	_info.item = this;

}

// Called every frame
void AMyItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyItem::OnMyCharacterOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromWeep, const FHitResult& SweepResult)
{

	auto character = Cast<AMyPlayer>(OtherActor);

	if (character == nullptr)
		return;

	auto player = Cast<AMyPlayerController>(character->GetController());

	if (character != nullptr && player != nullptr)
	{
		bool addSucceed = character->AddItem(this);
		if (addSucceed)
		{
			character->AddHp(30.0f);

			SetActorHiddenInGame(true);
			SetActorEnableCollision(false);
		}
	
	}
}

void AMyItem::OnMyCharacterOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}

void AMyItem::ItemDrop()
{
	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);
}

