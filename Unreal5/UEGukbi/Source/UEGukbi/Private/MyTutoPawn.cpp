// Fill out your copyright notice in the Description page of Project Settings.


#include "MyTutoPawn.h"
#include "Kismet/KismetMathLibrary.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"

// Sets default values
AMyTutoPawn::AMyTutoPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = _mesh;

	//sm에 해당 경로의 UStaticMesh, object를 갖고오는 방법. 생성자에서만 가능.
	static ConstructorHelpers::FObjectFinder<UStaticMesh> sm(TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Props/SM_Chair.SM_Chair'"));

	if (sm.Succeeded())
	{
		_mesh->SetStaticMesh(sm.Object);
	}

}

// Called when the game starts or when spawned
void AMyTutoPawn::BeginPlay()
{
	Super::BeginPlay();
	
	//UE_LOG(LogTemp, Log, TEXT("Begin!!"));
	//UE_LOG(LogTemp, Warning, TEXT("Begin!!"));

}

// Called every frame
void AMyTutoPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//UE_LOG(LogTemp, Error, TEXT("Deltatime : %f"), DeltaTime);




}

// Called to bind functionality to input
void AMyTutoPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* enhancedInputCompnent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (enhancedInputCompnent)
	{
		enhancedInputCompnent->BindAction(_moveAction, ETriggerEvent::Triggered, this, &AMyTutoPawn::Move);
	}
}

void AMyTutoPawn::Temp()
{
	UE_LOG(LogTemp, Error, TEXT("Temp"));
}

void AMyTutoPawn::Move(const FInputActionValue& value)
{
	FVector2D moveVector = value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		if (moveVector.Length() > 0.01f)
		{
			UE_LOG(LogTemp, Warning, TEXT("Y : %f"), moveVector.Y);
			UE_LOG(LogTemp, Warning, TEXT("X : %f"), moveVector.X);
		}

		FVector forWard = GetActorForwardVector() * moveVector.Y * 100.0f;
		FVector right = GetActorRightVector() * moveVector.X * 100.0f;

		FVector newLocation = GetActorLocation() + forWard + right;

		SetActorLocation(newLocation);
		//AddMovementInput(GetActorForwardVector(), moveVector.Y);
		//AddMovementInput(GetActorRightVector(), moveVector.X);

	}

}

