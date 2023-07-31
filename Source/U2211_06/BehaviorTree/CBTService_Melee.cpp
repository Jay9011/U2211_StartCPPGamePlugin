#include "BehaviorTree/CBTService_Melee.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Characters/CAIController.h"
#include "Characters/CEnemy_AI.h"
#include "Components/CStateComponent.h"
#include "Components/CAIBehaviorComponent.h"


UCBTService_Melee::UCBTService_Melee()
{
	NodeName = "Melee";

	Interval = 0.1f;
	RandomDeviation = 0.0f;
}

void UCBTService_Melee::TickNode(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	ACAIController* Controller = Cast<ACAIController>(OwnerComp.GetAIOwner());
	ACEnemy_AI* EnemyAI = Cast<ACEnemy_AI>(Controller->GetPawn());

	UCStateComponent* State = CHelpers::GetComponent<UCStateComponent>(EnemyAI);
	UCAIBehaviorComponent* Behavior = CHelpers::GetComponent<UCAIBehaviorComponent>(EnemyAI);

	if (State->IsHittedMode())
	{
		Behavior->SetHittedMode();
		return;
	}

	ACharacter* Target = Behavior->GetTarget();
	if(!Target)
	{
		Behavior->SetPatrolMode();

		return;
	}

	float Distance = EnemyAI->GetDistanceTo(Target);
	if (Distance < ActionRange)
	{
		Behavior->SetActionMode();

		return;
	}

	Behavior->SetApproachMode();
}
