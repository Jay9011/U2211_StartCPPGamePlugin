#pragma once

#include "CoreMinimal.h"
#include "Weapons/CDoAction.h"
#include "CDoAction_Bow.generated.h"

UCLASS(Blueprintable)
class U2211_06_API UCDoAction_Bow : public UCDoAction
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly, Category = "Arrow")
	TSubclassOf<class ACArrow> ArrowClass;
	
public:
	UCDoAction_Bow();

	void BeginPlay
	(
	   class ACAttachment* InAttachment,
	   class UCEquipment* InEquipment,
	   class ACharacter* InOwner,
	   const TArray<FDoActionData>& InDoActionData,
	   const TArray<FHitData>& InHitData
	) override;

	void DoAction() override;
	void Begin_DoAction() override;
	void End_DoAction() override;
	
	void OnBeginEquip() override;
	void OnUnequip() override;

	void Tick(float InDeltaTime) override;

public:
	void End_BowString();

private:
	void CreateArrow();
	class ACArrow* GetAttachedArrow();

private:
	UFUNCTION()
	void OnArrowHit(class AActor* InCauser, class ACharacter* InOtherCharacter);

	UFUNCTION()
	void OnArrowEndPlay(class ACArrow* InDestroyer);

private:
	class UPoseableMeshComponent* PoseableMesh;
	class USkeletalMeshComponent* SkeletalMesh;

private:
	bool bAttachedString = true;
	FVector OriginLocation;

private:
	float* Bend;

private:
	const bool* bEquipped;

private:
	TArray<class ACArrow*> Arrows;
};
