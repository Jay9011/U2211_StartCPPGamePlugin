#include "Weapons/DoActions/CDoAction_Bow.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Components/CStateComponent.h"
#include "Components/CMovementComponent.h"
#include "Weapons/Attachments/CAttachment_Bow.h"

UCDoAction_Bow::UCDoAction_Bow()
{
}

void UCDoAction_Bow::BeginPlay(ACAttachment* InAttachment, UCEquipment* InEquipment, ACharacter* InOwner, const TArray<FDoActionData>& InDoActionData, const TArray<FHitData>& InHitData)
{
	Super::BeginPlay(InAttachment, InEquipment, InOwner, InDoActionData, InHitData);

	ACAttachment_Bow* Bow = Cast<ACAttachment_Bow>(InAttachment);

	if (!!Bow)
	{
		bAttachedString = Bow->GetAttachedString();
		Bend = Bow->GetBend();
	}
}

void UCDoAction_Bow::DoAction()
{
	CheckFalse(State->IsIdleMode())
	CheckFalse(State->IsSubActionMode())
	
	Super::DoAction();

	DoActionDatas[0].DoAction(OwnerCharacter);
	
}

void UCDoAction_Bow::Begin_DoAction()
{
	Super::Begin_DoAction();
}

void UCDoAction_Bow::End_DoAction()
{
	Super::End_DoAction();
}

void UCDoAction_Bow::Tick(float InDeltaTime)
{
	Super::Tick(InDeltaTime);
}
