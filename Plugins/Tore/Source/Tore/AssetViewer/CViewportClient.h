#pragma once

#include "CoreMinimal.h"
#include "EditorViewportClient.h"

class FPreviewScene;
class SCViewport;

class TORE_API CViewportClient : public FEditorViewportClient
{
public:
	CViewportClient(FPreviewScene* InScene, const TSharedRef<SCViewport>& InViewport);
};
