#include "Tore.h"
#include "AssetToolsModule.h"
#include "AssetTools/CAssetTypeAction.h"

#define LOCTEXT_NAMESPACE "FToreModule"

void FToreModule::StartupModule()
{
	UE_LOG(LogTemp, Error, TEXT("Startup Tore Module"));

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
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FToreModule, Tore)