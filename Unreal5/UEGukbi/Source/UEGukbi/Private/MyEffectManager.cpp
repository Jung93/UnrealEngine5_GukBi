// Fill out your copyright notice in the Description page of Project Settings.


#include "MyEffectManager.h"

#include "NiagaraSystem.h"
// Sets default values
AMyEffectManager::AMyEffectManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>("RootComponent");

	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> particle(TEXT("/Script/Niagara.NiagaraSystem'/Game/Graphics/Effects/Vefects/Free_Fire/Shared/Particles/NS_Fire_Big_Simple.NS_Fire_Big_Simple'"));

	if (particle.Succeeded())
	{
		_particleTable.Add(TEXT("BigFire"), particle.Object);
		//_particleTable[TEXT("BigFire")] = particle.Object;
	}
}

// Called when the game starts or when spawned
void AMyEffectManager::BeginPlay()
{
	Super::BeginPlay();

	for (auto particle : _particleTable)
	{
		FString name = particle.Key;
		_effectTable.Add(name);

		for (int i = 0; i < 5;i++)
		{
			auto effect = GetWorld()->SpawnActor<AMyEffect>(FVector::ZeroVector, FRotator::ZeroRotator);
			effect->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
		
			effect->SetParticle(_particleTable[TEXT("BigFire")]);
			effect->Stop();

			_effectTable[name]._effects.Add(effect);
		}
	}
}

// Called every frame
void AMyEffectManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyEffectManager::PlayEffect(FString key, FVector pos)
{
	auto effects = _effectTable.Find(key);
	if (effects == nullptr)
		return;

	auto iter = effects->_effects.FindByPredicate([](AMyEffect* effect)->bool 
		{
			if (!effect->IsActive())
				return true;
			return false;
		});

	if (iter)
	{
		(*iter)->Play(pos);
	}

}

