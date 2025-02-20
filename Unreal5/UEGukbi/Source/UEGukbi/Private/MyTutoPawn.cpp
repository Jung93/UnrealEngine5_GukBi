// Fill out your copyright notice in the Description page of Project Settings.


#include "MyTutoPawn.h"
#include "Kismet/KismetMathLibrary.h"

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


	if (GetAttachParentActor() == nullptr)
	{
		FVector curLocation = GetActorLocation();
		FVector destLocation = curLocation + FVector(0, _moveSpeed, 0);
		SetActorLocation(destLocation);

		////Ptich(Y), Yaw(Z), Roll(X)
		//FRotator rot = FRotator(0, 1, 0);
		//AddActorLocalRotation(rot * _rotationSpeed * DeltaTime);
	}
	else
	{
		FVector parentV = GetAttachParentActor()->GetActorLocation();
		FVector myV = GetActorLocation();//WorldLocation

		FRotator rot = UKismetMathLibrary::FindLookAtRotation(myV, parentV);

		SetActorRotation(rot);
	}

	//Ptich(Y), Yaw(Z), Roll(X)
	FRotator rot = FRotator(0, 1, 0);
	AddActorLocalRotation(rot * _rotationSpeed * DeltaTime);

}

// Called to bind functionality to input
void AMyTutoPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

