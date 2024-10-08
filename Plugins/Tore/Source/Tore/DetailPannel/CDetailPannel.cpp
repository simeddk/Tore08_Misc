#include "CDetailPannel.h"
#include "DetailLayoutBuilder.h"
#include "DetailCategoryBuilder.h"
#include "DetailWidgetRow.h"
#include "DesktopPlatformModule.h"
#include "Interfaces/IMainFrameModule.h"
#include "Serialization/BufferArchive.h"
#include "Misc/FileHelper.h"
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
    //Open SaveDialog
    //-------------------------------------------------------------------------
    IMainFrameModule& MainFrame = FModuleManager::LoadModuleChecked<IMainFrameModule>("MainFrame");
    void* Handle = MainFrame.GetParentWindow()->GetNativeWindow()->GetOSWindowHandle();
    
    FString DefaultPath;
    FPaths::GetPath(DefaultPath);
    
    TArray<FString> FileNames;
    IDesktopPlatform* Platform = FDesktopPlatformModule::Get();
    Platform->SaveFileDialog(Handle, "Save Dialog", DefaultPath, "", "Mesh Binary File|*.bin", EFileDialogFlags::None, FileNames);
    
    if (FileNames.Num() < 1)
    {
        UE_LOG(LogTemp, Error, TEXT("File name is empty"));
        return FReply::Handled();
    }

    //-------------------------------------------------------------------------
    //Serialize to file(*.bin)
    //-------------------------------------------------------------------------
    FBinaryData SaveData;

    TArray<FColor> Colors;
    ColorBuffer.GetVertexColors(Colors);
    if (Colors.Num() < 1)
    {
        for (uint32 i = 0; i < VertexCount; i++)
        {
            Colors.Add(FColor::White);
        }
    }

    for (uint32 i = 0; i < VertexCount; i++)
    {
        SaveData.Positions.Add(PositionBuffer.VertexPosition(i));
        SaveData.Normals.Add(MetaBuffer.VertexTangentZ(i));
        SaveData.UVs.Add(MetaBuffer.GetVertexUV(i, 0));
        SaveData.Colors.Add(Colors[i]);
    }

    TArray<uint32> Indices;
    IndexBuffer.GetCopy(Indices);
    SaveData.Indices.Insert((int32*)Indices.GetData(), IndexCount, 0);

    FBufferArchive Buffer;
    Buffer << SaveData;
    
    FFileHelper::SaveArrayToFile(Buffer, *FileNames[0]);
    Buffer.Empty();

    FString Message;
    Message += FPaths::GetCleanFilename(FileNames[0]);
    Message += " saved file as binary.";
    GLog->Log(Message);

#ifdef AsCSV
    FString Contents;
    for (int32 i = 0; i < SaveData.Positions.Num(); i++)
    {
        Contents += SaveData.Positions[i].ToString() + ",";
        Contents += SaveData.Normals[i].ToString() + ",";
        Contents += SaveData.UVs[i].ToString() + ",";
        Contents += SaveData.Colors[i].ToString() + "\n";
    }

    FString WithoutExtension = FPaths::GetBaseFilename(FileNames[0], false);
    FString CSVFileName = WithoutExtension + ".csv";

    FFileHelper::SaveStringToFile(Contents, *CSVFileName);

    Message = "";
    Message += FPaths::GetCleanFilename(CSVFileName);
    Message += " saved file as csv.";
    GLog->Log(Message);
#endif

    return FReply::Unhandled();
}
