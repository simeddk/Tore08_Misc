#pragma once

#include "CoreMinimal.h"
#include "SEditorViewport.h"

class CViewportClient;
class FAdvancedPreviewScene;

class TORE_API SCViewport : public SEditorViewport, public FGCObject
{
public:
	SCViewport();

	void Construct(const FArguments& InArgs);

	TSharedRef<FAdvancedPreviewScene> GetScene();

public:
	virtual void AddReferencedObjects(FReferenceCollector& Collector) override;
	virtual TSharedRef<FEditorViewportClient> MakeEditorViewportClient() override;

private:
	TSharedPtr<FAdvancedPreviewScene> Scene;
	TSharedPtr<CViewportClient> Client;

private:
	UStaticMeshComponent* AssetMesh;
	UStaticMeshComponent* FloorMesh;
};
