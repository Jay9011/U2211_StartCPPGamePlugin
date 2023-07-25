#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CStatusComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class U2211_06_API UCStatusComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCStatusComponent();

protected:
	virtual void BeginPlay() override;		

public:
	void Damage(float InAmount);

private:
	UPROPERTY(EditAnywhere, Category = "Health")
	float MaxHealth = 100;

private:
	class ACharacter* OwnerCharacter;

private:
	float Health;

	
public:
	FORCEINLINE float GetHealth() { return Health; }
	FORCEINLINE float GetMaxHealth() { return MaxHealth; }
	FORCEINLINE bool IsDead() { return Health <= 0.0f; }

};
