// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnimInstance.h"
#include "MyCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Animation/AnimMontage.h"

UMyAnimInstance::UMyAnimInstance()
{
}

void UMyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	auto pawn = TryGetPawnOwner();

	AMyCharacter* character = Cast<AMyCharacter>(pawn);

	if (character != nullptr)
	{
		_speed = character->GetVelocity().Size();

		if (character->GetCharacterMovement()->IsFalling())
		{
			_isJump = true;
		}
		else
		{
			_isJump = false;
		}

		_vertical = character->GetMyVertical();
		_horizontal = character->GetMyHorizontal();


	}

}

void UMyAnimInstance::PlayAnimMontage()
{
	if (_animMontage == nullptr)
		return;

	if (!Montage_IsPlaying(_animMontage))
	{
		//_attackStart.Execute();
		//_attackStart3.Broadcast();
		//int result = _attackStart2.Execute(3, 3);
		//UE_LOG(LogTemp, Error, TEXT("Return value : %d"), result)

		Montage_Play(_animMontage);
	}

}

void UMyAnimInstance::AnimNotify_Attack_Hit()
{
	//auto pawn = TryGetPawnOwner();
	//AMyCharacter* character = Cast<AMyCharacter>(pawn);

	//character->Attack_Hit();

	_hitEvent.Broadcast();

}

void UMyAnimInstance::JumpToSection(int32 sectionIndex)
{
	//현재 공격 몽타주 Section1, Section2
	FName sectionName = FName(*FString::Printf(TEXT("Section%d"), sectionIndex));
	Montage_JumpToSection(sectionName);

}
