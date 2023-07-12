#pragma once

#include "CoreMinimal.h"
#include "Toolkits/AssetEditorToolkit.h"

class WEAPON_API FWeaponAssetEditor
	: public FAssetEditorToolkit
{
public:
	static void OpenWindow(FString InAssetName = "");
	static void Shutdown();

private:
	static TSharedPtr<FWeaponAssetEditor> Instance;

private:
	void Open(FString InAssetName);

protected:
	bool OnRequestClose() override;

public:
	virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;

private:
	void OnListViewSelectedItem(FWeaponRowDataPtr InPtr);

private:
	TSharedRef<SDockTab> Spawn_LeftAreaTab(const FSpawnTabArgs& InArgs);
	TSharedRef<SDockTab> Spawn_DetailsViewTab(const FSpawnTabArgs& InArgs);

public:
	virtual FName GetToolkitFName() const override;
	virtual FText GetBaseToolkitName() const override;
	virtual FString GetWorldCentricTabPrefix() const override;
	virtual FLinearColor GetWorldCentricTabColorScale() const override;

private:
	TSharedPtr<class SWeaponLeftArea> LeftArea;
	TSharedPtr<class IDetailsView> DetailsView;

private:
	static const FName EditorName;
	static const FName LeftAreaTabId;
	static const FName DetailTabId;

private:
	FReply OnClicked();
};
