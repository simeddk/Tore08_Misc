#pragma once

#include "CoreMinimal.h"
#include "IDetailCustomization.h"

struct FBinaryData
{
	TArray<FVector> Positions;
	TArray<FVector> Normals;
	TArray<FColor> Colors;
	TArray<FVector2D> UVs;
	TArray<int32> Indices;

	friend FArchive& operator<<(FArchive& LHS, FBinaryData& RHS)
	{
		return LHS
			<< RHS.Positions
			<< RHS.Normals
			<< RHS.UVs
			<< RHS.Colors
			<< RHS.Indices;
	}
};


class TORE_API CDetailPannel : public IDetailCustomization
{
public:
	static TSharedRef<IDetailCustomization> MakeInstance();

public:
	virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;

private:
	FReply OnClicked_ChangeColor();
	FReply OnClicked_SaveMesh();

private:
	TArray<TWeakObjectPtr<UObject>> Objects;
};
