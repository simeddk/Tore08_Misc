#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CLoadMeshActor.generated.h"

class UProceduralMeshComponent;

UCLASS()
class MISC_API ACLoadMeshActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ACLoadMeshActor();

	virtual void OnConstruction(const FTransform& Transform) override;

	void SetVertices
	(
		const TArray<FVector>& InPositions,
		const TArray<FVector>& InNormals,
		const TArray<FVector2D>& InUVs,
		const TArray<FColor>& InColors,
		const TArray<int32>& InIndices
	);
	
protected:
	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	UProceduralMeshComponent* ProcMeshComp;


private:
	TArray<FVector> Positions;
	TArray<FVector> Normals;
	TArray<FVector2D> UVs;
	TArray<FColor> Colors;
	TArray<int32> Indices;
};
