#include "Weapons/AddOns/CThornObject.h"
#include "Global.h"

#include "NiagaraComponent.h"
#include "GameFramework/Character.h"

ACThornObject::ACThornObject()
{
	CHelpers::CreateComponent<USceneComponent>(this, &Root, "Root");
	CHelpers::CreateComponent<UNiagaraComponent>(this, &Niagara, "Niagara", Root);
}

void ACThornObject::BeginPlay()
{
	Super::BeginPlay();

	Niagara->SetNiagaraVariableObject("Collision", this);
	Niagara->OnSystemFinished.AddDynamic(this, &ACThornObject::OnSystemFinished);

	if(!!NiagaraMesh)
	{
		BoxExtent = NiagaraMesh->GetBoundingBox().GetExtent();
	}
}

void ACThornObject::ReceiveParticleData_Implementation(const TArray<FBasicParticleData>& Data, UNiagaraSystem* NiagaraSystem)
{
	CheckFalse(Data.Num() > 0)

	static TArray<AActor*> ignores;
	ignores.AddUnique(GetOwner());

	static FHitResult hitResult;
	for(int32 i = Data.Num() - 1; i >= 0; i--)
	{
		FVector position = Data[i].Position + GetActorLocation();
		FVector scale = Data[i].Velocity * BoxExtent;

		// DrawDebugBox(GetWorld(), position, scale, FQuat(NiagaraMeshRotation), FColor::Green);
		UKismetSystemLibrary::BoxTraceSingleByProfile(GetWorld(), position, position, scale, NiagaraMeshRotation, "Pawn", false, ignores, EDrawDebugTrace::ForOneFrame, hitResult, true);

		if (hitResult.bBlockingHit)
		{
			float Height = 0;
			
			if (!!CollisionEffect)
			{
				ACharacter* HittedCharacter = Cast<ACharacter>(hitResult.GetActor());
				if(!!HittedCharacter)
					Height = HittedCharacter->GetCapsuleComponent()->GetScaledCapsuleHalfHeight() * 2.0f;
				
				FTransform transform = CollisionEffectTransform;

				FVector HitLocation = FVector(hitResult.Location.X, hitResult.Location.Y, hitResult.Location.Z - Height);
				transform.AddToTranslation(HitLocation);

				CHelpers::PlayEffect(GetWorld(), CollisionEffect, transform);
			}

         
			ACharacter* character = Cast<ACharacter>(hitResult.GetActor());
			if (!!character)
				HitData.SendDamage(Cast<ACharacter>(GetOwner()), this, character);
		}
	}
}

void ACThornObject::OnSystemFinished(UNiagaraComponent* PSystem)
{
	Destroy();
}
