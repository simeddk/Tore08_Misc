#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CHasDetailButton.generated.h"

UCLASS()
class MISC_API ACHasDetailButton : public AActor
{
	GENERATED_BODY()
	
public:	
	ACHasDetailButton();

	FORCEINLINE UStaticMeshComponent* GetMesh() { return MeshComp; }


#if WITH_EDITOR
public:
	void ChangeColor();
#endif

protected:
	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	UStaticMeshComponent* MeshComp;
};
