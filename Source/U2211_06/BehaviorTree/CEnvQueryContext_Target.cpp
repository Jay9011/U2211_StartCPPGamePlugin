#include "BehaviorTree/CEnvQueryContext_Target.h"
#include "Global.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/CAIController.h"
#include "Characters/CEnemy_AI.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"

void UCEnvQueryContext_Target::ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const
{
	Super::ProvideContext(QueryInstance, ContextData);

	ACEnemy_AI* ai = Cast<ACEnemy_AI>(QueryInstance.Owner.Get());
	ACAIController* controller = ai->GetController<ACAIController>();
	UBlackboardComponent* blackbord = controller->GetBlackboardComponent();
	AActor* target = Cast<AActor>(blackbord->GetValueAsObject("Target"));

	UEnvQueryItemType_Actor::SetContextHelper(ContextData, target);
}
