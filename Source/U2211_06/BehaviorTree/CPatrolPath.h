#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPatrolPath.generated.h"

UCLASS()
class U2211_06_API ACPatrolPath : public AActor
{
	GENERATED_BODY()
	
public:	
	ACPatrolPath();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
