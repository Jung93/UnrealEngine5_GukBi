// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "Kismet/KismetMathLibrary.h"

#include "Components/CapsuleComponent.h"

#include "MyAnimInstance.h"

#include "Engine/DamageEvents.h"

#include "MyStatComponent.h"
#include "Components/WidgetComponent.h"


// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//blueprint에서 skeletalMesh
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));


	_statComponent = CreateDefaultSubobject<UMyStatComponent>(TEXT("Stat"));

}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	_animInstance = Cast<UMyAnimInstance>(GetMesh()->GetAnimInstance());


	_animInstance->OnMontageEnded.AddDynamic(this, &AMyCharacter::AttackEnd);
	_animInstance->_hitEvent.AddUObject(this, &AMyCharacter::Attack_Hit);
	_animInstance->_deadEvent.AddUObject(this, &AMyCharacter::DeadEvent);




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

void AMyCharacter::DeadEvent()
{
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
}

float AMyCharacter::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	_statComponent->AddCurHp(-Damage);

	auto attackerController = Cast<APlayerController>(EventInstigator);

	if (attackerController)
	{
		// Player...
		if (IsDead())
		{
			UE_LOG(LogTemp, Error, TEXT("Be Dead by Player"));
		}
	}

	return Damage;
}

void AMyCharacter::AddHp(float amount)
{
	_statComponent->AddCurHp(amount);

}

bool AMyCharacter::IsDead()
{
	return _statComponent->IsDead();
}

