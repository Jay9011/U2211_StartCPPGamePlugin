#pragma once

#include "CoreMinimal.h"
#include "Weapons/CWeaponStructures.h"
#include "CDoAction.generated.h"

UCLASS(Abstract, NotBlueprintable)
class U2211_STARTCPPGAME_API UCDoAction : public UObject
{
	GENERATED_BODY()
public:
	UCDoAction();

public:
	virtual void BeginPlay
	(
		class ACAttachment* InAttachment,
		class UCEquipment* InEquipment,
		class ACharacter* InOwner,
		const TArray<FDoActionData>& InDoActionData,
		const TArray<FHitData>& InHitData
	);

	virtual void Tick(float InDeltaTime) {}
	
public:
	virtual void DoAction();
	virtual void Begin_DoAction();
	virtual void End_DoAction();

public:
   UFUNCTION()
      virtual void OnAttachmentBeginCollision() { }

   UFUNCTION()
      virtual void OnAttachmentEndCollision() { }

   UFUNCTION()
      virtual void OnAttachmentBeginOverlap(class ACharacter* InAttacker, AActor* InAttackCuaser, class ACharacter* InOther) { }

   UFUNCTION()
      virtual void OnAttachmentEndOverlap(class ACharacter* InAttacker, class ACharacter* InOther) { }

protected:
	bool bBeginAction;

	class ACharacter* OwnerCharacter;
	class UWorld* World;

	class UCMovementComponent* Movement;
	class UCStateComponent* State;

	TArray<FDoActionData> DoActionDatas;
	TArray<FHitData> HitDatas;
};
