#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapons/CWeaponStructures.h"
#include "CRotate_Object.generated.h"

UCLASS()
class U2211_STARTCPPGAME_API ACRotate_Object : public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	FHitData HitData;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Spawn")
	float Speed = 300;

	UPROPERTY(EditDefaultsOnly, Category = "Spawn")
	float Distance = 150;

	UPROPERTY(EditDefaultsOnly, Category = "Spawn")
	bool bNegative;

	UPROPERTY(EditDefaultsOnly, Category = "Spawn")
	float DamageInteval = 0.1f;

private:
	UPROPERTY(VisibleDefaultsOnly)
	class UCapsuleComponent* Capsule;

	UPROPERTY(VisibleDefaultsOnly)
	class UParticleSystemComponent* Particle;
	
public:	
	ACRotate_Object();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);

	virtual void Tick(float DeltaSeconds) override;

private:
	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void SendDamage();

private:
	float Angle;

	TArray<ACharacter*> Hitted;
	FTimerHandle TimerHandle;
};
