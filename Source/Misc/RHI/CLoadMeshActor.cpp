#include "CLoadMeshActor.h"
#include "ProceduralMeshComponent.h"

ACLoadMeshActor::ACLoadMeshActor()
{
	bRunConstructionScriptOnDrag = false;

	ProcMeshComp = CreateDefaultSubobject<UProceduralMeshComponent>("ProcMeshComp");
	RootComponent = ProcMeshComp;
}

void ACLoadMeshActor::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	ProcMeshComp->CreateMeshSection(0, Positions, Indices, Normals, UVs, Colors, TArray<FProcMeshTangent>(), true);
}

void ACLoadMeshActor::SetVertices(const TArray<FVector>& InPositions, const TArray<FVector>& InNormals, const TArray<FVector2D>& InUVs, const TArray<FColor>& InColors, const TArray<int32>& InIndices)
{
	Positions = InPositions;
	Normals = InNormals;
	UVs = InUVs;
	Colors = InColors;
	Indices = InIndices;

}
