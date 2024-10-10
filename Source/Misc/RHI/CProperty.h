#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CProperty.generated.h"

UCLASS()
class MISC_API UCProperty : public UObject
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Category = "Transform")
	FVector Location;

	UPROPERTY(EditAnywhere, Category = "Transform")
	FVector Scale;

};
