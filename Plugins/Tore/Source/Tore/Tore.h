#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class IAssetTypeActions;

class FToreModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
	TSharedPtr<IAssetTypeActions> AssetToolAction;
};
