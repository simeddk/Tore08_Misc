#include "CAssetViewer.h"

TSharedPtr<CAssetViewer> CAssetViewer::Instance = nullptr;
const static FName AppID = TEXT("ToreAssetViewer");
const static FName ViewportTabID = TEXT("ViewportTabID");
const static FName PreviewTabID = TEXT("PreviewTabID");
const static FName DetailsTabID = TEXT("DetailsTabID");

void CAssetViewer::OpenWindow(UObject* Property)
{
	if (Instance.IsValid())
	{
		Instance->CloseWindow();
		Instance.Reset();
	}

	Instance = MakeShareable(new CAssetViewer());
	Instance->OpenWindow_Internal(Property);
}

void CAssetViewer::Shutdown()
{
	if (Instance.IsValid())
	{
		Instance->CloseWindow();
	}
}

void CAssetViewer::OpenWindow_Internal(UObject* Property)
{
	TSharedRef<FTabManager::FLayout> Layout = FTabManager::NewLayout("ToreLayout")
		->AddArea
		(
			FTabManager::NewPrimaryArea()
			//ToolBar
			->SetOrientation(Orient_Vertical)
			->Split
			(
				FTabManager::NewStack()
				->SetSizeCoefficient(0.1f)
				->AddTab(GetToolbarTabId(), ETabState::OpenedTab)
			)

			//(LargeSpace)
			->Split
			(
				//(MiddleSpace) Viewport
				FTabManager::NewSplitter()
				->SetOrientation(Orient_Horizontal)
				->SetSizeCoefficient(0.75f)
				->Split
				(
					FTabManager::NewStack()
					->AddTab(ViewportTabID, ETabState::OpenedTab)
				)

				//(MiddleSpace) RightPannel
				->Split
				(
					//(SmallSpace) Preview
					FTabManager::NewSplitter()
					->SetOrientation(Orient_Vertical)
					->SetSizeCoefficient(0.5f)
					->Split
					(
						FTabManager::NewStack()
						->AddTab(PreviewTabID, ETabState::OpenedTab)
					)

					//(SmallSpace) Details
					->Split
					(
						FTabManager::NewStack()
						->AddTab(DetailsTabID, ETabState::OpenedTab)
					)
				)
			)
		);

	FAssetEditorToolkit::InitAssetEditor
	(
		EToolkitMode::Standalone,
		TSharedPtr<IToolkitHost>(),
		AppID,
		Layout,
		true,
		true,
		Property
	);
}

void CAssetViewer::RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	FAssetEditorToolkit::RegisterTabSpawners(InTabManager);

	TabManager->RegisterTabSpawner(ViewportTabID, FOnSpawnTab::CreateSP(this, &CAssetViewer::Spawn_ViewportTab));
}

TSharedRef<SDockTab> CAssetViewer::Spawn_ViewportTab(const FSpawnTabArgs& InArgs)
{
	return SNew(SDockTab)
		[
			SNew(SButton)
			.Text(FText::FromString("My Button"))
		];

}

FName CAssetViewer::GetToolkitFName() const
{
	return AppID;
}

FText CAssetViewer::GetBaseToolkitName() const
{
	return FText::FromName(AppID);
}

FString CAssetViewer::GetWorldCentricTabPrefix() const
{
	return AppID.ToString();
}

FLinearColor CAssetViewer::GetWorldCentricTabColorScale() const
{
	return FLinearColor::White;
}
