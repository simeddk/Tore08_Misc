#pragma once

#include "CoreMinimal.h"

class FSlateStyleSet;

class TORE_API CIconStyle
{
public:
	static TSharedPtr<CIconStyle> Get();
	static void Shutdown();

private:
	static TSharedPtr<CIconStyle> Instance;

public:
	CIconStyle();
	~CIconStyle();

private:
	void RegisterIcon(FSlateIcon& OutIcon, const FString& Postfix, const FString& ImagePath, const FVector2D& Size = FVector2D(48));

public:
	FSlateIcon LoadMeshIcon;
	FSlateIcon OpenViewerIcon;

private:
	const FName StyleSetName;
	TSharedPtr<FSlateStyleSet> StyleSet;
};
