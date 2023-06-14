#include "Weapons/SubAction/CSubAction_Fist.h"
#include "Global.h"

#include "GameFramework/Character.h"
#include "Components/CStateComponent.h"
#include "Components/CMovementComponent.h"
#include "Weapons/CAttachment.h"
#include "Weapons/CDoAction.h"

void UCSubAction_Fist::Pressed()
{
	CheckFalse(State->IsIdleMode())
	CheckTrue(State->IsSubActionMode())

	Super::Pressed();

	State->SetActionMode();
	State->OnSubActionMode();

	ActionData.DoAction(Owner);
}

void UCSubAction_Fist::Begin_SubAction_Implementation()
{
}

void UCSubAction_Fist::End_SubAction_Implementation()
{
	State->SetIdleMode();
	State->OffSubActionMode();

	Movement->Move();
	Movement->DisableFixedCamera();
}
