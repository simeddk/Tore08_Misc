#include "CMaterialData_Factory.h"
#include "CMaterialData.h"

UCMaterialData_Factory::UCMaterialData_Factory()
{
	bCreateNew = true;
	bEditAfterNew = true;
	SupportedClass = UCMaterialData::StaticClass();
}

UObject* UCMaterialData_Factory::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn, FName CallingContext)
{
	UE_LOG(LogTemp, Log, TEXT("%s is created as uasset file."), *GetNameSafe(InParent));
	return NewObject<UCMaterialData>(InParent, InClass, InName, Flags);
}
