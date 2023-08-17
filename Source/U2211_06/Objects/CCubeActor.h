#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CCubeActor.generated.h"

UCLASS()
class U2211_06_API ACCubeActor : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleDefaultsOnly)
	class UProceduralMeshComponent* Mesh;
	
public:	
	ACCubeActor();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	void AddTriangle(int32 InStart);
	
private:
	TArray<FVector> Positions;
	TArray<int32> Indices;
	TArray<FVector> Normals;
	TArray<FColor> Colors;
	TArray<FVector2D> Uvs;
};
