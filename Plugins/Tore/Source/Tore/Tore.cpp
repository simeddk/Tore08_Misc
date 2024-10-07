#include "Tore.h"
#include "LevelEditor.h"
#include "GameplayDebuggerCategory.h"
#include "GameplayDebugger.h"
#include "ToolBar/CButtonCommand.h"
#include "ToolBar/CIconStyle.h"
#include "AssetToolsModule.h"
#include "AssetTools/CAssetTypeAction.h"
#include "DebuggerCategory/CDebuggerCategory.h"
#include "DetailPannel/CDetailPannel.h"
#include "RHI/CHasDetailButton.h"


#define LOCTEXT_NAMESPACE "FToreModule"

void FToreModule::StartupModule()
{
	UE_LOG(LogTemp, Error, TEXT("Startup Tore Module"));

	//ToolBar
	{
		CButtonCommand::Register();
		CIconStyle::Get();

		Extender = MakeShareable(new FExtender());

		FToolBarExtensionDelegate AddLoadMeshButtonDelegate = FToolBarExtensionDelegate::CreateRaw(this, &FToreModule::AddLoadMeshButton);
		Extender->AddToolBarExtension("Misc", EExtensionHook::Before, CButtonCommand::Get().CommandList, AddLoadMeshButtonDelegate);

		FToolBarExtensionDelegate AddOpenViewerButtonDelegate = FToolBarExtensionDelegate::CreateRaw(this, &FToreModule::AddOpenViewerButton);
		Extender->AddToolBarExtension("Misc", EExtensionHook::Before, CButtonCommand::Get().CommandList, AddOpenViewerButtonDelegate);

		FLevelEditorModule& LevelEditor = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
		LevelEditor.GetToolBarExtensibilityManager()->AddExtender(Extender);
	}

	//GameplayDebuggerCategory
	{
		//FModuleManager::LoadModuleChecked<IGameplayDebugger>("GameplayDebugger");
		IGameplayDebugger& GameplayDebugger = IGameplayDebugger::Get();
		IGameplayDebugger::FOnGetCategory MakeInstanceDelegate = IGameplayDebugger::FOnGetCategory::CreateStatic(&CDebuggerCategory::MakeInstance);
		GameplayDebugger.RegisterCategory("ToreCategory", MakeInstanceDelegate, EGameplayDebuggerCategoryState::EnabledInGameAndSimulate, 7);
		GameplayDebugger.NotifyCategoriesChanged();
	}

	//DetailPannel
	{
		FPropertyEditorModule& PropertyEditor = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
		
		PropertyEditor.RegisterCustomClassLayout
		(
			ACHasDetailButton::StaticClass()->GetFName(), 
			FOnGetDetailCustomizationInstance::CreateStatic(&CDetailPannel::MakeInstance)
		);
	}

	//AssetTools
	{
		IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
		//EAssetTypeCategories::Type AssetCategory = EAssetTypeCategories::Misc;
		EAssetTypeCategories::Type AssetCategory =  AssetTools.RegisterAdvancedAssetCategory("MaterialData", FText::FromString("Material Data"));
		AssetToolAction = MakeShareable(new CAssetTypeAction(AssetCategory));
		AssetTools.RegisterAssetTypeActions(AssetToolAction.ToSharedRef());
	}
}

void FToreModule::ShutdownModule()
{
	UE_LOG(LogTemp, Error, TEXT("Shutdown Tore Module"));

	CIconStyle::Shutdown();

	if (IGameplayDebugger::IsAvailable())
	{
		IGameplayDebugger::Get().UnregisterCategory("ToreCategory");
	}
}

void FToreModule::AddLoadMeshButton(FToolBarBuilder& ToolBarBuilder)
{
	//FSlateIcon Icon = FSlateIcon(FEditorStyle::GetStyleSetName(), "LevelEditor.SelectMode");

	ToolBarBuilder.AddSeparator();
	ToolBarBuilder.AddToolBarButton
	(
		CButtonCommand::Get().LoadMeshButtonID,
		NAME_None,
		FText::FromString("Load Mesh"),
		FText::FromString("Load Mesh Data"),
		CIconStyle::Get()->LoadMeshIcon
	);
}

void FToreModule::AddOpenViewerButton(FToolBarBuilder& ToolBarBuilder)
{
	ToolBarBuilder.AddToolBarButton
	(
		CButtonCommand::Get().OpenViewerButtonID,
		NAME_None,
		FText::FromString("Open Viewer"),
		FText::FromString("Open My Viewer"),
		CIconStyle::Get()->OpenViewerIcon
	);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FToreModule, Tore)