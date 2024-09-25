#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AssetTools/CMaterialData.h"
#include "CMiku.generated.h"

class UDataTable;

UCLASS()
class MISC_API ACMiku : public ACharacter
{
	GENERATED_BODY()

public:
	ACMiku();

protected:
	virtual void OnConstruction(const FTransform& Transform) override;

public:	
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditAnywhere, Category = "Materials")
	UDataTable* MaterialData;

	UPROPERTY(EditAnywhere, Category = "Materials")
	ERenderType RenderType;
};
