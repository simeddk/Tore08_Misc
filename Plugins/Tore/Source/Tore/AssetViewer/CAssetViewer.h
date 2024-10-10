#pragma once

#include "CoreMinimal.h"
#include "Toolkits/AssetEditorToolkit.h"

class TORE_API CAssetViewer : public FAssetEditorToolkit
{
public:
	static void OpenWindow(UObject* Property);
	static void Shutdown();

private:
	void OpenWindow_Internal(UObject* Property);

private:
	virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;
	TSharedRef<SDockTab> Spawn_ViewportTab(const FSpawnTabArgs& InArgs);

public:
	virtual FName GetToolkitFName() const override;
	virtual FText GetBaseToolkitName() const override;
	virtual FString GetWorldCentricTabPrefix() const override;
	virtual FLinearColor GetWorldCentricTabColorScale() const override;

private:
	static TSharedPtr<CAssetViewer> Instance;

};
