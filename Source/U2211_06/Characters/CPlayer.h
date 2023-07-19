#pragma once

#include "CoreMinimal.h"
#include "ICharacter.h"
#include "GameFramework/Character.h"
#include "Components/CStateComponent.h"
#include "Parkour/CParkourComponent.h"
#include "CPlayer.generated.h"

/**
 * @brief Player Character
 */
UCLASS()
class U2211_06_API ACPlayer 
	: public ACharacter
	, public IICharacter
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere)
		class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere)
		class UCameraComponent* Camera;

private:
	UPROPERTY(VisibleAnywhere)
		class UCWeaponComponent* Weapon;

	UPROPERTY(VisibleAnywhere)
		class UCMontagesComponent* Montages;

	UPROPERTY(VisibleAnywhere)
		class UCMovementComponent* Movement;

	UPROPERTY(VisibleAnywhere)
		class UCStateComponent* State;

	UPROPERTY(VisibleDefaultsOnly)
	class UCParkourComponent* Parkour;

private:
	UPROPERTY(VisibleDefaultsOnly)
	class USceneComponent* ArrowGroup;

	UPROPERTY(VisibleDefaultsOnly)
	class UArrowComponent* Arrows[(int32)EParkourArrowType::Max];

public:
	ACPlayer();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UFUNCTION()
		void OnStateTypeChanged(EStateType InPrevType, EStateType InNewType);

private:
	void OnAvoid();

private:
	void Backstep();

public:
	void End_BackStep() override;
};
