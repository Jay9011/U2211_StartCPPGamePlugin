#pragma once

#include "CoreMinimal.h"
#include "Weapons/CAttachment.h"
#include "CAttachment_Bow.generated.h"

UCLASS()
class U2211_06_API ACAttachment_Bow : public ACAttachment
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly, Category = "View")
		FVector2D ViewPitchRange = FVector2D(-40, +30);

private:
	UPROPERTY(VisibleAnywhere)
		class USkeletalMeshComponent* SkeletalMesh;

	UPROPERTY(VisibleAnywhere)
		class UPoseableMeshComponent* PoseableMesh;
	
public:
	ACAttachment_Bow();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	
public:
	void OnBeginEquip_Implementation() override;
	void OnUnequip_Implementation() override;

private:
	FVector2D OriginViewPitchRange;

/*
 * Getter
 */	
public:
	float* GetBend();

};
