#pragma once

#include "CoreMinimal.h"
#include "Weapons/CDoAction.h"
#include "CDoAction_Bow.generated.h"

UCLASS()
class U2211_06_API UCDoAction_Bow : public UCDoAction
{
	GENERATED_BODY()

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

	void Tick(float InDeltaTime) override;

private:
	bool* bAttachedString;
	float* Bend;
};
