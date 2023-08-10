#include "BehaviorTree/CBTService_Range.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Characters/CAIController.h"
#include "Characters/CEnemy_AI.h"
#include "Components/CStateComponent.h"
#include "Components/CAIBehaviorComponent.h"

UCBTService_Range::UCBTService_Range()
{
	NodeName = "Range";

	Interval = 0.1f;
	RandomDeviation = 0.0f;
}

void UCBTService_Range::TickNode(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	ACAIController* controller = Cast<ACAIController>(OwnerComp.GetOwner());
	ACEnemy_AI* ai = Cast<ACEnemy_AI>(controller->GetPawn());
	UCStateComponent* state = CHelpers::GetComponent<UCStateComponent>(ai);
	UCAIBehaviorComponent* aiState = CHelpers::GetComponent<UCAIBehaviorComponent>(ai);

	if(bDrawDebug)
	{
		FVector start = ai->GetActorLocation();
		start.Z -= 25;

		FVector end = ai->GetActorLocation();
		end.Z += 25;

		DrawDebugCylinder(ai->GetWorld(), start, end, AvoidRange, 16, FColor::Red, false, Interval);
	}
	
	if (state->IsHittedMode())
	{
		aiState->SetHittedMode();

		return;
	}


	ACharacter* target = aiState->GetTarget();
	if (target == nullptr)
	{
		controller->ClearFocus(EAIFocusPriority::Gameplay);
		aiState->SetWaitMode();

		return;
	}


	controller->SetFocus(target);
   
	float distance = ai->GetDistanceTo(target);
	if (distance < AvoidRange)
	{
		aiState->SetAvoidMode();

		return;
	}

	aiState->SetActionMode();
}