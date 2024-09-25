#include "CMiku.h"
#include "Materials/MaterialInstanceConstant.h"

ACMiku::ACMiku()
{
	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("/Game/AMiku/Mesh/Appearance_Miku"));
	if (MeshAsset.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(MeshAsset.Object);
	}

	GetMesh()->SetRelativeLocation(FVector(0, 0, -88));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));
}

void ACMiku::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	if (MaterialData)
	{
		TArray<FMaterialElementData*> ReadDatas;
		MaterialData->GetAllRows("", ReadDatas);

		if (ReadDatas[(int32)RenderType] && ReadDatas[(int32)RenderType]->DataAsset)
		{
			UCMaterialData* SelectedDataAsset = ReadDatas[(int32)RenderType]->DataAsset;

			for (int32 i = 0; i < (int32)EMaterialElementType::Max; i++)
			{
				//Todo. SelectedDataAsset->Materials[i] check null
				GetMesh()->SetMaterial(i, SelectedDataAsset->Materials[i]);
			}
		}
	}
}

void ACMiku::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

