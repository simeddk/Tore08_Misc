#include "CDetailPannel.h"
#include "DetailLayoutBuilder.h"
#include "DetailCategoryBuilder.h"
#include "DetailWidgetRow.h"
#include "DesktopPlatformModule.h"
#include "RHI/CHasDetailButton.h"

TSharedRef<IDetailCustomization> CDetailPannel::MakeInstance()
{
    return MakeShareable(new CDetailPannel());
}

void CDetailPannel::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
    IDetailCategoryBuilder& CategoryBuilder = DetailBuilder.EditCategory("Tore");
    
    CategoryBuilder.AddCustomRow(FText::FromString("Tore"))
    .NameContent()
    [
        SNew(STextBlock)
        .Text(FText::FromString("Color"))
    ]
    .ValueContent()
    .VAlign(VAlign_Center)
    .MaxDesiredWidth(250)
    [
        SNew(SButton)
        .OnClicked(this, &CDetailPannel::OnClicked_ChangeColor)
        .Content()
        [
            SNew(STextBlock)
            .Text(FText::FromString("Change"))
        ]
    ];

    CategoryBuilder.AddCustomRow(FText::FromString("Tore"))
    .NameContent()
    [
        SNew(STextBlock)
        .Text(FText::FromString("Vertices"))
    ]
    .ValueContent()
    .VAlign(VAlign_Center)
    .MaxDesiredWidth(250)
    [
        SNew(SButton)
        .OnClicked(this, &CDetailPannel::OnClicked_SaveMesh)
        .Content()
        [
            SNew(STextBlock)
            .Text(FText::FromString("Save to binary file"))
        ]
    ];

    DetailBuilder.GetObjectsBeingCustomized(Objects);
}

FReply CDetailPannel::OnClicked_ChangeColor()
{
    GLog->Log(GetNameSafe(Objects[0].Get()));

    ACHasDetailButton* HasButtonActor = Cast<ACHasDetailButton>(Objects[0].Get());
    if (!HasButtonActor)
    {
        return FReply::Handled();
    }

    HasButtonActor->ChangeColor();

    return FReply::Unhandled();
}

FReply CDetailPannel::OnClicked_SaveMesh()
{
    //-------------------------------------------------------------------------
    //Get Vertex Datas
    //-------------------------------------------------------------------------
    ACHasDetailButton* HasButtonActor = Cast<ACHasDetailButton>(Objects[0].Get());
    UStaticMeshComponent* MeshComp = HasButtonActor->GetMesh();

    UStaticMesh* MeshAsset = MeshComp->GetStaticMesh();
    if (!MeshAsset)
    {
        return FReply::Handled();
    }
    
    FStaticMeshRenderData* RenderData = MeshAsset->RenderData.Get();
    if (RenderData->LODResources.Num() < 1)
    {
        return FReply::Handled();
    }

    FStaticMeshLODResources& LOD = RenderData->LODResources[0];
    
    FPositionVertexBuffer& PositionBuffer = LOD.VertexBuffers.PositionVertexBuffer;
    FStaticMeshVertexBuffer& MetaBuffer = LOD.VertexBuffers.StaticMeshVertexBuffer;
    FColorVertexBuffer& ColorBuffer = LOD.VertexBuffers.ColorVertexBuffer;
    FRawStaticIndexBuffer& IndexBuffer = LOD.IndexBuffer;

    if (PositionBuffer.GetNumVertices() < 1 || IndexBuffer.GetNumIndices() < 1)
    {
        return FReply::Handled();
    }

    uint32 VertexCount = PositionBuffer.GetNumVertices();
    int32 IndexCount = IndexBuffer.GetNumIndices();

    GLog->Logf(TEXT("Vertex Count : %d"), VertexCount);
    GLog->Logf(TEXT("Index Count : %d"), IndexCount);


    //-------------------------------------------------------------------------
    //Serialize to file(*.bin)
    //-------------------------------------------------------------------------
    IDesktopPlatform* Platform = FDesktopPlatformModule::Get();
    //Todo. Platform->SaveFileDialog

    return FReply::Unhandled();
}
