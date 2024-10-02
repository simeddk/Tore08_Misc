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

	FString Name = StyleSetName.ToString() + "." + "LoadMeshIcon";

	FString Path = IPluginManager::Get().FindPlugin("Tore")->GetBaseDir();
	Path /= "Resources";
	StyleSet->SetContentRoot(Path);

	FSlateImageBrush* ImageBrush = new FSlateImageBrush(Path / "Icon.png", FVector2D(48));
	StyleSet->Set(FName(Name), ImageBrush);

	LoadMeshIcon = FSlateIcon(StyleSetName, FName(Name));

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
