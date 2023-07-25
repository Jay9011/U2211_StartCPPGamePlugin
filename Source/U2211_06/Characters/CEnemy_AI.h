#pragma once

#include "CoreMinimal.h"
#include "Characters/CEnemy.h"
#include "CEnemy_AI.generated.h"

/**
 * @brief Enemy AI class
 */
UCLASS()
class U2211_06_API ACEnemy_AI : public ACEnemy
{
	GENERATED_BODY()

public:
	ACEnemy_AI();
	
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	class UBehaviorTree* BehaviorTree;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	uint8 TeamID = 2;


private:
	UPROPERTY(VisibleDefaultsOnly)
	class UCWeaponComponent* Weapon;

	UPROPERTY(VisibleDefaultsOnly)
	class UCAIBehaviorComponent* Behavior;
	
#if WITH_EDITOR
private:
	void UpdateLabelRenderScale();
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "Label")
	float LabelViewAmount = 3000.0f;
	
	UPROPERTY(VisibleDefaultsOnly)
	class UWidgetComponent* LabelWidget;
#endif

public:
	FORCEINLINE uint8 GetTeamID() { return TeamID; }
	FORCEINLINE class UBehaviorTree* GetBehaviorTree() { return BehaviorTree; }
};
