#include "Notifies/CAnimNotifyState_CameraAnim.h"
#include "Global.h"

#include "GameFramework/Character.h"
#include "GameFramework/PlayerController.h"
#include "Camera/PlayerCameraManager.h"
#include "Camera/CameraAnim.h"
#include "Weapons/AddOns/CCameraModifier.h"

FString UCAnimNotifyState_CameraAnim::GetNotifyName_Implementation() const
{
	return "CameraAnim";
}

void UCAnimNotifyState_CameraAnim::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	CheckNull(MeshComp)
	CheckNull(MeshComp->GetOwner())
	CheckNull(CameraAnim)

	ACharacter* character = Cast<ACharacter>(MeshComp->GetOwner());
	CheckNull(character)

	APlayerController* controller = character->GetController<APlayerController>();
	CheckNull(controller)

	ACharacter* target = character;
	if(Target.IsNull() == false)
	{
		target = Target.Get();
	}

	UCameraModifier* modifier = controller->PlayerCameraManager->AddNewCameraModifier(UCCameraModifier::StaticClass());
	Modifier = Cast<UCCameraModifier>(modifier);

	//카메라 애니메이션을 시작하기 전에 카메라 위치를 설정한다.
	FVector location = target->GetActorLocation();

	//카메라 위치를 캐릭터의 위치에서 LocationOffset만큼 떨어진 곳으로 설정한다.
	float yaw = controller->GetControlRotation().Yaw;
	location += FRotator(0, yaw, 0).RotateVector(LocationOffset);

	//카메라 위치를 설정하고 카메라 회전값을 설정한다.
	Modifier->SetLocation(location);
	Modifier->SetRotation(FRotator(PitchOffset, yaw, 0));

	//컨트롤러의 회전값을 설정한다.
	controller->SetControlRotation(FRotator(0, controller->GetControlRotation().Yaw, 0));

	//카메라 애니메이션을 재생한다.
	controller->PlayerCameraManager->PlayCameraAnim(CameraAnim, PlayRatio, 1, BlendInTime, BlendOutTime, false, false, 0, ECameraShakePlaySpace::UserDefined,controller->GetControlRotation());
}

void UCAnimNotifyState_CameraAnim::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	CheckNull(MeshComp)
	CheckNull(MeshComp->GetOwner())
	CheckNull(CameraAnim)

	ACharacter* character = Cast<ACharacter>(MeshComp->GetOwner());
	CheckNull(character)

	//카메라 애니메이션을 끝내고 카메라 위치를 원래대로 돌려놓는다.
	APlayerController* controller = character->GetController<APlayerController>();
	CheckNull(controller)

	controller->PlayerCameraManager->RemoveCameraModifier(Modifier);
}
