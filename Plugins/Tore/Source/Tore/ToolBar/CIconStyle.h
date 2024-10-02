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

public:
	FSlateIcon LoadMeshIcon;

private:
	const FName StyleSetName;
	TSharedPtr<FSlateStyleSet> StyleSet;
};
