#pragma once

#include "CoreMinimal.h"
#include "GameplayDebuggerCategory.h"

struct FCollectData
{
	FString Name;
	FVector Loation;
	FVector Forward;
};

class TORE_API CDebuggerCategory : public FGameplayDebuggerCategory
{
public:
	CDebuggerCategory();
	~CDebuggerCategory();

public:
	static TSharedRef<FGameplayDebuggerCategory> MakeInstance();

public:
	virtual void CollectData(APlayerController* OwnerPC, AActor* DebugActor) override;
	virtual void DrawData(APlayerController* OwnerPC, FGameplayDebuggerCanvasContext& CanvasContext) override;

private:
	FCollectData PlayerData;
	FCollectData ForwardActorData;
	FCollectData DebugActorData;
};
