// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

UCLASS()
class UEGUKBI_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	UFUNCTION()
	void AttackEnd(class UAnimMontage* Montage, bool bInterrupted);

	float GetMyVertical() { return _vertical; }
	float GetMyHorizontal() { return _horizontal; }

	void Attack_Hit();
	void DeadEvent();

	void AddHp(float amount);
	void AddExp(int32 amount);
	void AttackBuff(float amount);

	virtual float TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	bool IsDead();
	bool IsAttacking() { return _isAttack; }

	float AttackRange() { return _attackRange; }

	//언리얼의 핵심구조
	//1. 상속
	//2. 컴포넌트
	//
	//컴포넌트 패턴 조사
	//1. Actor 컴포넌트
	//2. Scene 컴포넌트

protected:
	UPROPERTY()
	class UMyAnimInstance* _animInstance;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stat", meta = (AllowPrivateAccess = "true"))
	class UMyStatComponent* _statComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation", meta = (AllowPrivateAccess = "true"))
	bool _isAttack;


	int32 _curAttackSection = 1;

	float _vertical = 0.0f;
	float _horizontal = 0.0f;

	UPROPERTY(EditAnywhere)
	float _attackRange = 400.0f;

	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI", meta = (AllowPrivateAccess = "true"))
	//class UWidgetComponent* _hpBarWidget;
};
