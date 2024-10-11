#include "CViewportClient.h"
#include "SCViewport.h"

CViewportClient::CViewportClient(FPreviewScene* InScene, const TSharedRef<SCViewport>& InViewport)
	: FEditorViewportClient(nullptr, InScene, StaticCastSharedRef<SCViewport>(InViewport))
{
	SetViewMode(EViewModeIndex::VMI_Lit);

	SetViewRotation(FRotator(-45.f, -45.f, 0.f));
	SetViewLocationForOrbiting(FVector(0, 0, 75), 250.f);
}