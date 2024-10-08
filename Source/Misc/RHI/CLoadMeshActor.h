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
		const TArray<FVector>& Positions,
		const TArray<FVector>& Normals,
		const TArray<FVector2D>& UVs,
		const TArray<FColor>& Colors,
		const TArray<int32>& Indices
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
