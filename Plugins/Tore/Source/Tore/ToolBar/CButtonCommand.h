#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"

class TORE_API CButtonCommand : public TCommands<CButtonCommand>
{
public:
	CButtonCommand();
	~CButtonCommand();

public:
	virtual void RegisterCommands() override;

private:
	void OnLoadMeshButtonClicked();
	void OnOpenViewerButtonClicked();

public:
	TSharedPtr<FUICommandInfo> LoadMeshButtonID;
	TSharedPtr<FUICommandInfo> OpenViewerButtonID;

	TSharedPtr<FUICommandList> CommandList;
};
