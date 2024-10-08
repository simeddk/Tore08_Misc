#include "CButtonCommand.h"
#include "DesktopPlatformModule.h"
#include "Interfaces/IMainFrameModule.h"
#include "Serialization/BufferArchive.h"
#include "Misc/FileHelper.h"
#include "LevelEditorViewport.h"
#include "DetailPannel/CDetailPannel.h"
#include "RHI/CLoadMeshActor.h"

CButtonCommand::CButtonCommand()
	: TCommands("Tore", FText::FromString("My Command"), NAME_None, FEditorStyle::GetStyleSetName())
{
	CommandList = MakeShareable(new FUICommandList());
}

CButtonCommand::~CButtonCommand()
{
	if (CommandList.IsValid())
	{
		CommandList.Reset();
	}
}

#define LOCTEXT_NAMESPACE "Tore"
void CButtonCommand::RegisterCommands()
{
	UI_COMMAND(LoadMeshButtonID, "LoadMesh", "Load Mesh Data", EUserInterfaceActionType::Button, FInputChord());
	UI_COMMAND(OpenViewerButtonID, "OpenViewer", "Open My Viewer", EUserInterfaceActionType::Button, FInputChord());

	CommandList->MapAction
	(
		LoadMeshButtonID,
		FExecuteAction::CreateRaw(this, &CButtonCommand::OnLoadMeshButtonClicked),
		FCanExecuteAction()
	);

	CommandList->MapAction
	(
		OpenViewerButtonID,
		FExecuteAction::CreateRaw(this, &CButtonCommand::OnOpenViewerButtonClicked),
		FCanExecuteAction()
	);
}
#undef LOCTEXT_NAMESPACE

void CButtonCommand::OnLoadMeshButtonClicked()
{
	UE_LOG(LogTemp, Warning, TEXT("%s"), TEXT(__FUNCTION__));

	//-------------------------------------------------------------------------
	//Open OpenDialog
	//-------------------------------------------------------------------------
	IMainFrameModule& MainFrame = FModuleManager::LoadModuleChecked<IMainFrameModule>("MainFrame");
	void* Handle = MainFrame.GetParentWindow()->GetNativeWindow()->GetOSWindowHandle();

	FString DefaultPath;
	FPaths::GetPath(DefaultPath);

	TArray<FString> FileNames;
	IDesktopPlatform* Platform = FDesktopPlatformModule::Get();
	Platform->OpenFileDialog(Handle, "Open Dialog", DefaultPath, "", "Mesh Binary File|*.bin", EFileDialogFlags::None, FileNames);

	if (FileNames.Num() < 1)
	{
		UE_LOG(LogTemp, Error, TEXT("File name is empty"));
		return;
	}

	//-------------------------------------------------------------------------
	//Serialize to Memory(*.bin)
	//-------------------------------------------------------------------------
	FBufferArchive Buffer;
	FFileHelper::LoadFileToArray(Buffer, *FileNames[0]);
	FMemoryReader Reader = FMemoryReader(Buffer, true);
	Buffer.Seek(0);

	FBinaryData LoadData;
	Reader << LoadData;
	Reader.Close();

	GLog->Logf(TEXT("Vertex Count : %d"), LoadData.Positions.Num());
	GLog->Logf(TEXT("Index Count : %d"), LoadData.Indices.Num());

#ifdef AsCSV
	FString Contents;
	for (int32 i = 0; i < LoadData.Positions.Num(); i++)
	{
		Contents += LoadData.Positions[i].ToString() + ",";
		Contents += LoadData.Normals[i].ToString() + ",";
		Contents += LoadData.UVs[i].ToString() + ",";
		Contents += LoadData.Colors[i].ToString() + "\n";
	}

	FString WithoutExtension = FPaths::GetBaseFilename(FileNames[0], false);
	FString CSVFileName = WithoutExtension + "_Loaded.csv";

	FFileHelper::SaveStringToFile(Contents, *CSVFileName);

	FString Message = "";
	Message += FPaths::GetCleanFilename(CSVFileName);
	Message += " saved file as csv.";
	GLog->Log(Message);
#endif

	//-------------------------------------------------------------------------
	//Spawn ProcMesh Actor
	//-------------------------------------------------------------------------
	UWorld* World = GEditor->GetEditorWorldContext().World();
	
	FLevelEditorViewportClient* Client =(FLevelEditorViewportClient*)GEditor->GetActiveViewport()->GetClient();

	FVector Start = Client->GetViewLocation();
	FVector End = ;

	FHitResult Hit;
	World->LineTraceSingleByChannel(Hit, );

	FTransform TM;

	ACLoadMeshActor* SpawnedActor = World->SpawnActorDeferred<ACLoadMeshActor>
	(
		ACLoadMeshActor::StaticClass(),
		TM,
		nullptr,
		nullptr,
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn
	);

	SpawnedActor->SetVertices(LoadData.Positions, LoadData.Normals, LoadData.UVs, LoadData.Colors, LoadData.Indices);

	SpawnedActor->FinishSpawning(TM);
}

void CButtonCommand::OnOpenViewerButtonClicked()
{
	UE_LOG(LogTemp, Warning, TEXT("%s"), TEXT(__FUNCTION__));
}
