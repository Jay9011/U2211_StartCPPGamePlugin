#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Components/CFeetComponent.h"
#include "Components/CWeaponComponent.h"
#include "CAnimInstance.generated.h"

UCLASS()
class U2211_06_API UCAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadOnly, Category = "Animation")
		float Speed;

	UPROPERTY(BlueprintReadOnly, Category = "Animation")
		float Pitch;

	UPROPERTY(BlueprintReadOnly, Category = "Animation")
		float Direction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
	bool bFalling;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "InverseKinemetics")
	bool bFeet;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "InverseKinemetics")
	FFeetData FeetData;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Bow")
		bool bBow_Aiming;

protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Animation")
		EWeaponType WeaponType = EWeaponType::Max;

public:
	void NativeBeginPlay() override;
	void NativeUpdateAnimation(float DeltaSeconds) override;

private:
	UFUNCTION()
		void OnWeaponTypeChanged(EWeaponType InPrevType, EWeaponType InNewType);

private:
	class ACharacter* OwnerCharacter;
	class UCWeaponComponent* Weapon;

private:
	FRotator PrevRotation;
};
