#include "Weapons/DoActions/CDoAction_Bow.h"
#include "Global.h"
#include "Components/CMovementComponent.h"
#include "Components/CStateComponent.h"
#include "Components/PoseableMeshComponent.h"
#include "GameFramework/Character.h"
#include "Weapons/CEquipment.h"
#include "Weapons/Attachments/CAttachment_Bow.h"

UCDoAction_Bow::UCDoAction_Bow()
{
}

void UCDoAction_Bow::BeginPlay(ACAttachment* InAttachment, UCEquipment* InEquipment, ACharacter* InOwner, const TArray<FDoActionData>& InDoActionData, const TArray<FHitData>& InHitData)
{
	Super::BeginPlay(InAttachment, InEquipment, InOwner, InDoActionData, InHitData);

	ACAttachment_Bow* Bow = Cast<ACAttachment_Bow>(InAttachment);

	PoseableMesh = CHelpers::GetComponent<UPoseableMeshComponent>(InAttachment);
	SkeletalMesh = CHelpers::GetComponent<USkeletalMeshComponent>(InAttachment);
	
	if (!!Bow)
	{
		Bend = Bow->GetBend();
	}

	OriginLocation = PoseableMesh->GetBoneLocationByName("bow_string_mid", EBoneSpaces::ComponentSpace);

	bEquipped = InEquipment->GetEquipped();
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
	
	bAttachedString = false;
   
	*Bend = 0;
	PoseableMesh->SetBoneLocationByName("bow_string_mid", OriginLocation, EBoneSpaces::ComponentSpace);
}

void UCDoAction_Bow::End_DoAction()
{
	Super::End_DoAction();
}

void UCDoAction_Bow::OnBeginEquip()
{
	Super::OnBeginEquip();
	
	OwnerCharacter->GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void UCDoAction_Bow::OnUnequip()
{
	Super::OnUnequip();
	
	OwnerCharacter->GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

	*Bend = 0;
	PoseableMesh->SetBoneLocationByName("bow_string_mid", OriginLocation, EBoneSpaces::ComponentSpace);
}

void UCDoAction_Bow::Tick(float InDeltaTime)
{
	Super::Tick(InDeltaTime);

	PoseableMesh->CopyPoseFromSkeletalComponent(SkeletalMesh);

	bool bCheck = true;
	bCheck &= (*bEquipped == true);
	bCheck &= (bBeginAction == false);
	bCheck &= (bAttachedString == true);

	CheckFalse(bCheck);

	FVector handLocation = OwnerCharacter->GetMesh()->GetSocketLocation("Hand_Bow_Right");
	PoseableMesh->SetBoneLocationByName("bow_string_mid", handLocation, EBoneSpaces::WorldSpace);
}

void UCDoAction_Bow::End_BowString()
{
	*Bend = 100;
	bAttachedString = true;
}
