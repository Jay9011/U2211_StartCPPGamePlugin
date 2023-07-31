#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CAIBehaviorComponent.generated.h"

UENUM(BlueprintType)
enum class EAIStateType : uint8
{
	Wait = 0, Approach, Action, Patrol, Hitted, Avoid, Dead,
	Max
 };
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FAIStateTypeChanged, EAIStateType, InPrevType, EAIStateType, InNewType);


UCLASS()
class U2211_06_API UCAIBehaviorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCAIBehaviorComponent();

protected:
	virtual void BeginPlay() override;

private:
	EAIStateType GetType();

public:
	class ACharacter* GetTarget();
	
public:
	bool IsWaitMode();
	bool IsApproachMode();
	bool IsActionMode();
	bool IsPatrolMode();
	bool IsHittedMode();
	bool IsAvoidMode();
	bool IsDeadMode();
	
public:
	void SetWaitMode();
	void SetApproachMode();
	void SetActionMode();
	void SetPatrolMode();
	void SetHittedMode();
	void SetAvoidMode();
	void SetDeadMode();

public:
	FVector GetPatrolLocation();
	void SetPatrolLocation(const FVector& InLocation);

	
private:
	UPROPERTY(EditAnywhere, Category = "Key")
	FName AIStateTypeKey = "AIState";

	UPROPERTY(EditAnywhere, Category = "Key")
	FName TargetKey = "Target";
	
	UPROPERTY(EditAnywhere, Category = "Key")
	FName PatrolLocationKey = "PatrolLocation";

private:
	void ChangeType(EAIStateType InType);

public:
	FAIStateTypeChanged OnAIStateTypeChanged;

private:
	class UBlackboardComponent* Blackboard;

	
public:
	FORCEINLINE void SetBlackboard(class UBlackboardComponent* InBlackboard) { Blackboard = InBlackboard; }

};
