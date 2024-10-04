#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class IAssetTypeActions;
class FToolBarBuilder;

class FToreModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
	void AddLoadMeshButton(FToolBarBuilder& ToolBarBuilder);
	void AddOpenViewerButton(FToolBarBuilder& ToolBarBuilder);

private:
	TSharedPtr<FExtender> Extender;
	TSharedPtr<IAssetTypeActions> AssetToolAction;
};
