#include "SCViewport.h"
#include "CViewportClient.h"
#include "AdvancedPreviewScene.h" //Todo.

SCViewport::SCViewport()
{
    
}

void SCViewport::AddReferencedObjects(FReferenceCollector& Collector)
{
    Collector.AddReferencedObject(AssetMesh);
    Collector.AddReferencedObject(FloorMesh);
}

TSharedRef<FEditorViewportClient> SCViewport::MakeEditorViewportClient()
{
    Client = MakeShareable(new CViewportClient(Scene.Get(), SharedThis(this)));

    return Client.ToSharedRef();
}