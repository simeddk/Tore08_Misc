#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "CMaterialData.generated.h"

class UMaterialInstanceConstant;

//-----------------------------------------------------------------------------
// Enums
//-----------------------------------------------------------------------------
UENUM(BlueprintType)
enum class ERenderType : uint8
{
	None, Matcap, Floor, Ramp, Smoothstep, Max
};

UENUM(BlueprintType)
enum class EMaterialElementType : uint8
{
	Skin, Hair, HairShadow, HairBackspace, ClothBlack,
	ClothSpecular, Cloth, Cloth2, Cloth3, ClothNoEdge,
	ClothNoEdge2, Face, SkinNoEdge, Eye, SkinNoEdge2,
	Max
};

//-----------------------------------------------------------------------------
// Struct - TableRowBase
//-----------------------------------------------------------------------------
USTRUCT(BlueprintType)
struct FMaterialElementData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	ERenderType RenderType;

	UPROPERTY(EditAnywhere)
	UCMaterialData* DataAsset;
};

//-----------------------------------------------------------------------------
// Class - DataAsset
//-----------------------------------------------------------------------------
UCLASS()
class TORE_API UCMaterialData : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, Category = "Materials")
	UMaterialInstanceConstant* Materials[(int32)EMaterialElementType::Max];

};
