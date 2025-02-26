// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

#include "MyAnimInstance.h"

// Sets default values
AMyCharacter::AMyCharacter()
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
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	_animInstance = Cast<UMyAnimInstance>(GetMesh()->GetAnimInstance());

	//Delegate 바인딩 연습. delegate는 UI 쪽에서 많이 쓰임
	_animInstance->_attackStart.BindUObject(this, &AMyCharacter::TestDelegate);
	_animInstance->_attackStart2.BindUObject(this, &AMyCharacter::TestDelegateInt);
	_animInstance->_attackStart3.AddDynamic(this, &AMyCharacter::TestDelegate);
	_animInstance->OnMontageEnded.AddDynamic(this, &AMyCharacter::AttackEnd);

	_animInstance->_hitEvent.AddUObject(this, &AMyCharacter::Attack_Hit);
}


// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* enhancedInputCompnent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (enhancedInputCompnent)
	{
		enhancedInputCompnent->BindAction(_moveAction, ETriggerEvent::Triggered, this, &AMyCharacter::Move);
		enhancedInputCompnent->BindAction(_lookAction, ETriggerEvent::Triggered, this, &AMyCharacter::Look);
		enhancedInputCompnent->BindAction(_jumpAction, ETriggerEvent::Triggered, this, &AMyCharacter::Jump);
		enhancedInputCompnent->BindAction(_attackAction, ETriggerEvent::Triggered, this, &AMyCharacter::Attack);
	}

}

void AMyCharacter::Move(const FInputActionValue& value)
{
	if (_isAttack)
		return;
	FVector2D moveVector = value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		if (moveVector.Length() > 0.01f)
		{
			//UE_LOG(LogTemp, Warning, TEXT("Y : %f"), moveVector.Y);
			//UE_LOG(LogTemp, Warning, TEXT("X : %f"), moveVector.X);

			FVector forWard = GetActorForwardVector();
			FVector right = GetActorRightVector();

			_vertical = moveVector.Y;
			_horizontal = moveVector.X;

			AddMovementInput(forWard, moveVector.Y * _speed);
			AddMovementInput(right, moveVector.X * _speed);


		}
	}
}

void AMyCharacter::Look(const FInputActionValue& value)
{
	FVector2D lookAxisVector = value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(lookAxisVector.X);

	}
}

void AMyCharacter::Attack(const FInputActionValue& value)
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

void AMyCharacter::TestDelegate()
{
	UE_LOG(LogTemp, Warning, TEXT("delegate call"))

}

int AMyCharacter::TestDelegateInt(int a = 1, int b = 1)
{
	int result = a + b;
	UE_LOG(LogTemp, Warning, TEXT("delegate call : %d"), result)

	return a * b;
}

void AMyCharacter::AttackEnd(UAnimMontage* Montage, bool bInterrupted)
{
	_isAttack = false;
}

void AMyCharacter::Attack_Hit()
{
	FHitResult hitResult;
	FCollisionQueryParams params(NAME_None, false, this);

	float attackRange = 400.0f;
	float radius = 100.0f;

	FQuat Rotation = FQuat(GetActorForwardVector().ToOrientationQuat()) * FQuat(FVector::RightVector, FMath::DegreesToRadians(90.0f));//FQuat(GetActorForwardVector().ToOrientationQuat());// *FQuat(FVector::RightVector, FMath::DegreesToRadians(90.0f));

	bool bResult = GetWorld()->SweepSingleByChannel
	(
		OUT hitResult,
		GetActorLocation(),
		GetActorLocation() + GetActorForwardVector() * (attackRange),
		Rotation,
		ECC_GameTraceChannel2,
		FCollisionShape::MakeCapsule(radius, attackRange),
		params
	);

	FColor drawColor = FColor::Green;

	if (bResult && hitResult.GetActor()->IsValidLowLevel())
	{
		drawColor = FColor::Red;
	}

	DrawDebugCapsule(GetWorld(), GetActorLocation(), attackRange *0.5f, radius, Rotation, drawColor, false, 1.0f);
}

