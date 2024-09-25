#pragma once

#include "CoreMinimal.h"
#include "AssetTypeActions_Base.h"

class TORE_API CAssetTypeAction : public FAssetTypeActions_Base
{
public:
	CAssetTypeAction(EAssetTypeCategories::Type InAssetCategory);
	~CAssetTypeAction();

	virtual FText GetName() const override;
	virtual UClass* GetSupportedClass() const override;
	virtual FColor GetTypeColor() const override;
	virtual uint32 GetCategories() override;

private:
	EAssetTypeCategories::Type AssetCategory;
};
