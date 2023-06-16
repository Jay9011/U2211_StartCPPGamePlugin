#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "CAnimNotifyState_CameraAnim.generated.h"

UCLASS()
class U2211_STARTCPPGAME_API UCAnimNotifyState_CameraAnim : public UAnimNotifyState
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Category = "Camera")
	class UCameraAnim* CameraAnim;

	UPROPERTY(EditAnywhere, Category = "Camera")
	float PlayRatio = 1;

	UPROPERTY(EditAnywhere, Category = "Camera")
	float BlendInTime = 0;
	
	UPROPERTY(EditAnywhere, Category = "Camera")
	float BlendOutTime = 0;

	UPROPERTY(EditAnywhere, Category = "Camera")
	TSoftObjectPtr<class ACharacter> Target;
	
public:
	FString GetNotifyName_Implementation() const override;
};
