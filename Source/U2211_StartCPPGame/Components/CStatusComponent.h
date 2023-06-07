// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CStatusComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class U2211_STARTCPPGAME_API UCStatusComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	FORCEINLINE float GetHealth() { return Health; }
	FORCEINLINE bool IsDead() { return Health <= 0; }

public:
	UCStatusComponent();

protected:
	virtual void BeginPlay() override;

public:
	void Damage(float InAmount);

private:
	class ACharacter* OwnerCharacter;

private:
	float Health;
	float MaxHealth = 100;
		
};
