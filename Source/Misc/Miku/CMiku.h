#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AssetTools/CMaterialData.h"
#include "CMiku.generated.h"

class UDataTable;
class UMaterialInstanceConstant;

UCLASS()
class MISC_API ACMiku : public ACharacter
{
	GENERATED_BODY()

public:
	ACMiku();

protected:
	virtual void OnConstruction(const FTransform& Transform) override;


#if WITH_EDITOR
protected:
	void SetLightDirectionToMaterials(FVector InDirection);
#endif

protected:
	UPROPERTY(EditAnywhere, Category = "AMiku")
	UDataTable* MaterialData;

	UPROPERTY(EditAnywhere, Category = "AMiku")
	ERenderType RenderType;

	UPROPERTY(EditAnywhere, Category = "AMiku", meta = (ClampMax = 1.00, ClampMin = -1.00))
	FVector LightDirection;

private:
	TArray<UMaterialInstanceConstant*> MikuMaterials;
};
