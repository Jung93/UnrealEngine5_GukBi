// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyCharacter.h"
#include "MyMonster.generated.h"

/**
 * 
 */


UCLASS()
class UEGUKBI_API AMyMonster : public AMyCharacter
{
	GENERATED_BODY()
	
public:
	AMyMonster();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void SpawnItem();
	virtual float TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

private:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI", meta = (AllowPrivateAccess = "true"))
	class UWidgetComponent* _hpBarWidget;

	UPROPERTY(EditAnywhere, Category = "EXP", meta = (AllowPrivateAccess = "true"))
	int32 _monsterExp;
	//UPROPERTY(EditAnywhere, Category = "Item")
	//TSubclassOf<class AMyItem> _item;



};
