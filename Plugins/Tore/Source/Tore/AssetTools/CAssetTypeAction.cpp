#include "CAssetTypeAction.h"
#include "CMaterialData.h"

CAssetTypeAction::CAssetTypeAction(EAssetTypeCategories::Type InAssetCategory)
	: AssetCategory(InAssetCategory)
{
	
}

CAssetTypeAction::~CAssetTypeAction()
{
}

FText CAssetTypeAction::GetName() const
{
	return FText::FromString(TEXT("Material Data"));
}

UClass* CAssetTypeAction::GetSupportedClass() const
{
	return UCMaterialData::StaticClass();
}

FColor CAssetTypeAction::GetTypeColor() const
{
	return FColor::Black;
}

uint32 CAssetTypeAction::GetCategories()
{
	return AssetCategory;
}
