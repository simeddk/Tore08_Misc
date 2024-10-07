#pragma once

#include "CoreMinimal.h"
#include "IDetailCustomization.h"

class TORE_API CDetailPannel : public IDetailCustomization
{
public:
	static TSharedRef<IDetailCustomization> MakeInstance();

public:
	virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;

private:
	FReply OnClicked_ChangeColor();
	FReply OnClicked_SaveMesh();

private:
	TArray<TWeakObjectPtr<UObject>> Objects;
};
