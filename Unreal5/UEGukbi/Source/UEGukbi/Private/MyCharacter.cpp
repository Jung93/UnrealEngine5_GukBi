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

#include "Engine/DamageEvents.h"

#include "MyStatComponent.h"
#include "Components/WidgetComponent.h"
#include "MyHpBar.h"

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

	_statComponent = CreateDefaultSubobject<UMyStatComponent>(TEXT("Stat"));
	_hpBarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HpBar"));
	_hpBarWidget->SetupAttachment(GetMesh());
	_hpBarWidget->SetWidgetSpace(EWidgetSpace::World);

	static ConstructorHelpers::FClassFinder<UMyHpBar> hpBarClass(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/BluePrints/BP_MyHpBar.BP_MyHpBar_C'"));

	if(hpBarClass.Succeeded())
	{
		_hpBarWidget->SetWidgetClass(hpBarClass.Class);
	}
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

	auto hpBar = Cast<UMyHpBar>(_hpBarWidget->GetWidget());

	if (hpBar != nullptr)
	{
		_statComponent->_hpChanged.AddUObject(hpBar, &UMyHpBar::SetHpBarValue);

	}


}


// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto playerCameraManager = GetWorld()->GetFirstPlayerController()->PlayerCameraManager;

	if (playerCameraManager != nullptr)
	{
		FVector hpBarLocation = _hpBarWidget->GetComponentLocation();
		FVector cameraLocation = playerCameraManager->GetCameraLocation();

		FRotator rot = UKismetMathLibrary::FindLookAtRotation(hpBarLocation, cameraLocation);

		_hpBarWidget->SetWorldRotation(rot);

	}


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
			FVector forWard = GetActorForwardVector();
			FVector right = GetActorRightVector();

			_vertical = moveVector.Y;
			_horizontal = moveVector.X;

			AddMovementInput(forWard, moveVector.Y * _statComponent->GetSpeed());
			AddMovementInput(right, moveVector.X * _statComponent->GetSpeed());
		}
	}
}

void AMyCharacter::Look(const FInputActionValue& value)
{
	FVector2D lookAxisVector = value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(lookAxisVector.X);
		AddControllerPitchInput(-lookAxisVector.Y);
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

	float attackRange = 800.0f;
	float radius = 100.0f;

	FQuat Rotation = FQuat::FindBetweenVectors(FVector(0, 0, 1), GetActorForwardVector());

	FVector center = GetActorLocation() + GetActorForwardVector() * (attackRange * 0.5f);
	FVector start = GetActorLocation() + GetActorForwardVector() * (attackRange * 0.5f);
	FVector end = GetActorLocation() + GetActorForwardVector() * (attackRange * 0.5f);

	bool bResult = GetWorld()->SweepSingleByChannel
	(
		OUT hitResult,
		start,//같은 값으로 두면 capsule이 움직이지 않고 멈춰선 채 충돌감지
		end,
		Rotation,
		ECC_GameTraceChannel2,
		FCollisionShape::MakeCapsule(radius, attackRange * 0.5f),
		params
	);

	FColor drawColor = FColor::Green;

	if (bResult && hitResult.GetActor()->IsValidLowLevel())
	{
		drawColor = FColor::Red;

		AMyCharacter* victim = Cast<AMyCharacter>(hitResult.GetActor());

		if (victim != nullptr)
		{
			FDamageEvent damageEvent = FDamageEvent();
			victim->TakeDamage(_statComponent->GetAtk(), damageEvent, GetController(), this);
		}

	}

	DrawDebugCapsule(GetWorld(), center, attackRange *0.5f, radius, Rotation, drawColor, false, 1.0f);
}

float AMyCharacter::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	_statComponent->AddCurHp(-Damage);

	return Damage;
}

void AMyCharacter::AddHp(float amount)
{
	_statComponent->AddCurHp(amount);

}

