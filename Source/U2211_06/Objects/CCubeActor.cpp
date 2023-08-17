#include "Objects/CCubeActor.h"
#include "Global.h"
#include "ProceduralMeshComponent.h"

ACCubeActor::ACCubeActor()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickInterval = 1.0f;

	CHelpers::CreateComponent<UProceduralMeshComponent>(this, &Mesh, "Mesh");


	FVector p = FVector(0.5f, 0.5f, 0.5f);

	//Front
	Positions.Add(FVector(-p.X, -p.Y, -p.Z)); // 0
	Positions.Add(FVector(-p.X, -p.Y, +p.Z)); // 1
	Positions.Add(FVector(-p.X, +p.Y, -p.Z)); // 2
	Positions.Add(FVector(-p.X, +p.Y, +p.Z)); // 3

	for (int32 i = 0; i < 4; i++)
	{
		Colors.Add(FColor(128, 0, 0, 255));
		Normals.Add(FVector(-1, 0, 0));
	}
	AddTriangle(0);

	//Back
	Positions.Add(FVector(+p.X, +p.Y, -p.Z));
	Positions.Add(FVector(+p.X, +p.Y, +p.Z));
	Positions.Add(FVector(+p.X, -p.Y, -p.Z));
	Positions.Add(FVector(+p.X, -p.Y, +p.Z));

	for (int32 i = 0; i < 4; i++)
	{
		Colors.Add(FColor(0, 128, 0, 255));
		Normals.Add(FVector(+1, 0, 0));
	}
	AddTriangle(4);

	//Top
	Positions.Add(FVector(-p.X, -p.Y, +p.Z));
	Positions.Add(FVector(+p.X, -p.Y, +p.Z));
	Positions.Add(FVector(-p.X, +p.Y, +p.Z));
	Positions.Add(FVector(+p.X, +p.Y, +p.Z));

	for (int32 i = 0; i < 4; i++)
	{
		Colors.Add(FColor(0, 0, 128, 255));
		Normals.Add(FVector(0, 0, +1));
	}
	AddTriangle(8);
	
	//Bottom
	Positions.Add(FVector(-p.X, -p.Y, -p.X));
	Positions.Add(FVector(-p.X, +p.Y, -p.X));
	Positions.Add(FVector(+p.X, -p.Y, -p.X));
	Positions.Add(FVector(+p.X, +p.Y, -p.X));

	for (int32 i = 0; i < 4; i++)
	{
		Colors.Add(FColor(128, 128, 0, 255));
		Normals.Add(FVector(0, 0, -1));
	}
	AddTriangle(12);

	//Left
	Positions.Add(FVector(+p.X, -p.Y, -p.Z));
	Positions.Add(FVector(+p.X, -p.Y, +p.Z));
	Positions.Add(FVector(-p.X, -p.Y, -p.Z));
	Positions.Add(FVector(-p.X, -p.Y, +p.Z));

	for (int32 i = 0; i < 4; i++)
	{
		Colors.Add(FColor(128, 0, 128, 255));
		Normals.Add(FVector(0, -1, 0));
	}
	AddTriangle(16);


	//Right
	Positions.Add(FVector(-p.X, +p.Y, -p.Z));
	Positions.Add(FVector(-p.X, +p.Y, +p.Z));
	Positions.Add(FVector(+p.X, +p.Y, -p.Z));
	Positions.Add(FVector(+p.X, +p.Y, +p.Z));

	for (int32 i = 0; i < 4; i++)
	{
		Colors.Add(FColor(128, 128, 128, 255));
		Normals.Add(FVector(0, +1, 0));
	}
	AddTriangle(20);


	
	for (int32 i = 0; i < Positions.Num() / 4; i++)
	{
		Uvs.Add(FVector2D(0, 1));
		Uvs.Add(FVector2D(0, 0));
		Uvs.Add(FVector2D(1, 1));
		Uvs.Add(FVector2D(1, 0));
	}

	Mesh->CreateMeshSection(0, Positions, Indices, Normals, Uvs, Colors, TArray<FProcMeshTangent>(), true);
	Mesh->SetRelativeScale3D(FVector(100));
}

void ACCubeActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACCubeActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	for (int32 i = 0; i < Colors.Num() / 4; i++)
	{
		FColor color = FColor::MakeRandomColor();
		color.A = 255;

		Colors[i * 4 + 0] = color;
		Colors[i * 4 + 1] = color;
		Colors[i * 4 + 2] = color;
		Colors[i * 4 + 3] = color;
	}

	Mesh->UpdateMeshSection(0, Positions, Normals, Uvs, Colors, TArray<FProcMeshTangent>());
}

void ACCubeActor::AddTriangle(int32 InStart)
{
	Indices.Add(InStart + 2);
	Indices.Add(InStart + 1);
	Indices.Add(InStart + 0);

	Indices.Add(InStart + 3);
	Indices.Add(InStart + 1);
	Indices.Add(InStart + 2);
}

