// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MyAnimInstance.generated.h"

/**
 * 
 */

//void(void)
DECLARE_DELEGATE(AnimDelegateTest)
//int(int,int)
DECLARE_DELEGATE_RetVal_TwoParams(int, AnimDelegateTestInt, int, int)

//dynamic 붙으면 블루프린트에서도 볼 수 있음. 컨벤션 F 붙어야함
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAnimDelegateTest3);

DECLARE_MULTICAST_DELEGATE(FAttackHitEvent);

UCLASS()
class UEGUKBI_API UMyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UMyAnimInstance();
	
	virtual void NativeUpdateAnimation(float DeltaSeconds);
	
	UFUNCTION()//블루프린트에서 함수호출 하려면 BlueprintCallable 추가
	void PlayAnimMontage();

	UFUNCTION()
	void AnimNotify_Attack_Hit();

	void JumpToSection(int32 sectionIndex);

	AnimDelegateTest _attackStart;
	AnimDelegateTestInt _attackStart2;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pawn", meta = (AllowPrivateAccess = "true"))
	FAnimDelegateTest3 _attackStart3;
	FAttackHitEvent _hitEvent;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pawn", meta = (AllowPrivateAccess = "true"))
	float _speed = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pawn", meta = (AllowPrivateAccess = "true"))
	bool _isJump = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AnimMontage", meta = (AllowPrivateAccess = "true"))
	class UAnimMontage* _animMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AnimMontage", meta = (AllowPrivateAccess = "true"))
	float _vertical;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AnimMontage", meta = (AllowPrivateAccess = "true"))
	float _horizontal;
};
