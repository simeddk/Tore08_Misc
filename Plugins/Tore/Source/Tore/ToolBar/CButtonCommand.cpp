#include "CButtonCommand.h"

CButtonCommand::CButtonCommand()
	: TCommands("Tore", FText::FromString("My Command"), NAME_None, FEditorStyle::GetStyleSetName())
{
	LoadMeshCommandList = MakeShareable(new FUICommandList());
}

CButtonCommand::~CButtonCommand()
{
	if (LoadMeshCommandList.IsValid())
	{
		LoadMeshCommandList.Reset();
	}
}

#define LOCTEXT_NAMESPACE "Tore"
void CButtonCommand::RegisterCommands()
{
	UI_COMMAND(LoadMeshButtonID, "LoadMesh", "Load Mesh Data", EUserInterfaceActionType::Button, FInputChord());

	LoadMeshCommandList->MapAction
	(
		LoadMeshButtonID,
		FExecuteAction::CreateRaw(this, &CButtonCommand::OnLoadMeshButtonClicked),
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