#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "CMaterialData_Factory.generated.h"

UCLASS()
class TORE_API UCMaterialData_Factory : public UFactory
{
	GENERATED_BODY()
	
public:
	UCMaterialData_Factory();

	virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn, FName CallingContext) override;

};
