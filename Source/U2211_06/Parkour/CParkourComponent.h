#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "Kismet/KismetSystemLibrary.h"
#include "CParkourComponent.generated.h"

/**
 * @brief Parkour Arrow Type
 */
UENUM(BlueprintType)
enum class EParkourArrowType : uint8
{
	Center = 0, Ceil, Floor, Left, Right, Land, Max,
 };

/**
 * @brief Parkour Type
 */
UENUM(BlueprintType)
enum class EParkourType : uint8
{
	Climb = 0, Fall, Slide, Short, Normal, Wall, Max,
 };

/**
 * @brief Parkour Data
 */
USTRUCT(BlueprintType)
struct FParkourData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	EParkourType Type;

	UPROPERTY(EditAnywhere)
	UAnimMontage* Montage;

	UPROPERTY(EditAnywhere)
	float PlayRatio = 1;

	UPROPERTY(EditAnywhere)
	FName SectionName;

	UPROPERTY(EditAnywhere)
	float MinDistance;

	UPROPERTY(EditAnywhere)
	float MaxDistance;

	UPROPERTY(EditAnywhere)
	float Extent;

	UPROPERTY(EditAnywhere)
	bool bFixedCamera;
public:
	void PlayMontage(class ACharacter* InCharacter);
};

/**
 * @brief Parkour Component
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class U2211_06_API UCParkourComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Category = "Data")
	UDataTable* DataTable;

private:
	UPROPERTY(EditAnywhere, Category = "Trace")
	float TraceDistance = 600;

	UPROPERTY(EditAnywhere, Category = "Trace")
	TEnumAsByte<EDrawDebugTrace::Type> DebugType;

	UPROPERTY(EditAnywhere, Category = "Trace")
	float AvailableFrontAngle = 15;
	
public:	
	UCParkourComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	void LineTrace(EParkourArrowType InType);
	void CheckTrace_Center();

private:
	TMap<EParkourType, TArray<FParkourData>> DataMap;

private:
   class ACharacter* OwnerCharacter;
   class UArrowComponent* Arrows[(int32)EParkourArrowType::Max];

private:
	FHitResult HitResults[(int32)EParkourArrowType::Max];

private:
	//Center Trace Result
	AActor* HitObstacle;
	FVector HitObstacleExtent;
	float HitDistance;
	float ToFrontYaw;
};
