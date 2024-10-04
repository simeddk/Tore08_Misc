#include "CButtonCommand.h"

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

	TArray<const FSlateBrush*> Brushes;
	FEditorStyle::GetResources(Brushes);

	for (const auto& Brush : Brushes)
	{
		GLog->Log(Brush->GetResourceName().ToString());
	}
}

void CButtonCommand::OnOpenViewerButtonClicked()
{
	UE_LOG(LogTemp, Warning, TEXT("%s"), TEXT(__FUNCTION__));
}
