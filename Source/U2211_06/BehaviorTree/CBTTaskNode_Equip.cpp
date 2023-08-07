#include "BehaviorTree/CBTTaskNode_Equip.h"
#include "Global.h"
#include "Characters/CEnemy_AI.h"
#include "Characters/CAIController.h"
#include "Components/CStateComponent.h"
#include "Components/CWeaponComponent.h"
#include "Weapons/CEquipment.h"

UCBTTaskNode_Equip::UCBTTaskNode_Equip()
{
	NodeName = "Equip";

	bNotifyTick = true;
}

EBTNodeResult::Type UCBTTaskNode_Equip::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	ACAIController* controller = Cast<ACAIController>(OwnerComp.GetOwner());
	ACEnemy_AI* ai = Cast<ACEnemy_AI>(controller->GetPawn());

	UCWeaponComponent* weapon = CHelpers::GetComponent<UCWeaponComponent>(ai);
	CheckNullResult(weapon, EBTNodeResult::Failed);

	if(Type == weapon->GetWeaponType())
		return EBTNodeResult::Succeeded;

	switch (Type)
	{
	case EWeaponType::Fist: break;
	case EWeaponType::Sword: weapon->SetSwordMode(); break;
	case EWeaponType::Hammer: break;
	case EWeaponType::Warp: break;
	case EWeaponType::Around: break;
	case EWeaponType::Bow: break;
	case EWeaponType::Max: break;
	default: ;
	}

	return EBTNodeResult::InProgress;
}

void UCBTTaskNode_Equip::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	ACAIController* controller = Cast<ACAIController>(OwnerComp.GetOwner());
	ACEnemy_AI* ai = Cast<ACEnemy_AI>(controller->GetPawn());

	UCWeaponComponent* weapon = CHelpers::GetComponent<UCWeaponComponent>(ai);
	const bool* bEquipped = weapon->GetEquipment()->GetEquipped();

	UCStateComponent* state = CHelpers::GetComponent<UCStateComponent>(ai);
	if(state->IsIdleMode() && *bEquipped)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);

		return;
	}
}
