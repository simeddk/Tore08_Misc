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

void ACLoadMeshActor::SetVertices(const TArray<FVector>& Positions, const TArray<FVector>& Normals, const TArray<FVector2D>& UVs, const TArray<FColor>& Colors, const TArray<int32>& Indices)
{
	this->Positions = Positions;
	this->Normals = Normals;
	this->UVs = UVs;
	this->Colors = Colors;
	this->Indices = Indices;

}
