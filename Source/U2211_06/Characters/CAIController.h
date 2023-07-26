#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "CAIController.generated.h"
/**
 * @brief AI controller
 */
UCLASS()
class U2211_06_API ACAIController : public AAIController
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere)
	class UAIPerceptionComponent* Perception;
	
public:
	ACAIController();

protected:
	virtual void BeginPlay() override;

protected:
	void OnPossess(APawn* InPawn) override;
	void OnUnPossess() override;

private:
	UFUNCTION()
	void OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors);
	
private:
	class ACEnemy_AI* Enemy;
	class UCAIBehaviorComponent* Behavior;

private:
	class UAISenseConfig_Sight* Sight;
};
