#include "CIconStyle.h"
#include "Styling/SlateStyle.h"
#include "Styling/SlateStyleRegistry.h"
#include "Interfaces/IPluginManager.h"

TSharedPtr<CIconStyle> CIconStyle::Instance = nullptr;

TSharedPtr<CIconStyle> CIconStyle::Get()
{
	if (!Instance)
	{
		Instance = MakeShareable(new CIconStyle());
	}

	return Instance;
}

void CIconStyle::Shutdown()
{
	if (Instance.IsValid())
	{
		Instance.Reset();
	}
}

CIconStyle::CIconStyle()
	: StyleSetName("ToreStyle")
{
	StyleSet = MakeShareable(new FSlateStyleSet(StyleSetName));

	FString Path = IPluginManager::Get().FindPlugin("Tore")->GetBaseDir();
	Path /= "Resources";
	StyleSet->SetContentRoot(Path);

	RegisterIcon(LoadMeshIcon, "LoadMesh", Path / "Icon.png");
	RegisterIcon(OpenViewerIcon, "OpenViewer", Path / "Icon2.png");

	FSlateStyleRegistry::RegisterSlateStyle(*StyleSet.Get());
}

CIconStyle::~CIconStyle()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(StyleSetName);

	if (StyleSet.IsValid())
	{
		StyleSet.Reset();
	}
}

void CIconStyle::RegisterIcon(FSlateIcon& OutIcon, const FString& Postfix, const FString& ImagePath, const FVector2D& Size)
{
	FString Name = StyleSetName.ToString() + "." + Postfix;
	FSlateImageBrush* ImageBrush = new FSlateImageBrush(ImagePath, Size);
	StyleSet->Set(FName(Name), ImageBrush);

	OutIcon = FSlateIcon(StyleSetName, FName(Name));
}
