#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"

class WEAPON_API FWeaponCommand
	: public TCommands<FWeaponCommand>
{
public:
	FWeaponCommand();
	~FWeaponCommand();

	void Startup();

public:
	void RegisterCommands() override;

private:
	TSharedPtr<FUICommandList> Command;

	TSharedPtr<FExtender> Extender;
	TSharedPtr<FUICommandInfo> Id;

private:
	void AddToolBar(FToolBarBuilder& InBuilder);
	void OnClicked();
};
