#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/Views/STableRow.h"

struct FWeaponRowData
{
	int Number = 1;
	FString Name;
	class UCWeaponAsset* Asset = nullptr;
	
	FWeaponRowData() {}
	FWeaponRowData(int32 InNumber, FString InName, class UCWeaponAsset* InAsset)
	  : Number(InNumber), Name(InName), Asset(InAsset)
	{
	}

	static TSharedPtr<FWeaponRowData> Make(int32 InNumber, FString InName, class UCWeaponAsset* InAsset)
	{
		return MakeShareable(new FWeaponRowData(InNumber, InName, InAsset));
	}
};
typedef TSharedPtr<FWeaponRowData> FWeaponRowDataPtr;

/******************************************************
 * SWeaponTableRow
 ******************************************************/
class WEAPON_API SWeaponTableRow
	: public SMultiColumnTableRow<FWeaponRowDataPtr>
{
	SLATE_BEGIN_ARGS(SWeaponTableRow) {}
	SLATE_ARGUMENT(FWeaponRowDataPtr, Row)
	SLATE_END_ARGS()

public:
	void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTable);

protected:
	TSharedRef<SWidget> GenerateWidgetForColumn(const FName& InColumnName) override;

private:
	FWeaponRowDataPtr Row;
};
typedef SListView<FWeaponRowDataPtr> SWeaponListView;

/******************************************************
 *  SWeaponListView
 ******************************************************/
DECLARE_DELEGATE_OneParam(FOnWeaponListViewSelectedItem, FWeaponRowDataPtr);

class WEAPON_API SWeaponLeftArea
	: public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SWeaponLeftArea) {}
	SLATE_EVENT(FOnWeaponListViewSelectedItem, OnWeaponListViewSelectedItem)
	SLATE_END_ARGS()

public:
	void Construct(const FArguments& InArgs);

public:
	FWeaponRowDataPtr GetFirstDataPtr() { return RowDatas[0]; }

	bool HasRowPtrs() { return RowDatas.Num() > 0; }
	void SelectDataPtr(class UCWeaponAsset* InAsset);

	FWeaponRowDataPtr GetRowDataPtrByName(const FString& InAssetName);
	FString SelectedRowDataPtrName();
	
private:
	TSharedRef<ITableRow> OnGenerateRow(FWeaponRowDataPtr InRow, const TSharedRef<STableViewBase>& InTable);
	void OnSelectionChanged(FWeaponRowDataPtr InPtr, ESelectInfo::Type InType);

	void OnTextChanged(const FText& InText);
	void OnTextCommitted(const FText& InText, ETextCommit::Type InType);
	
private:
	FText OnGetAssetCount() const;

private:
	void ReadDataAssetList();

private:
	FOnWeaponListViewSelectedItem OnWeaponListViewSelectedItem;
	
private:
	TArray<FWeaponRowDataPtr> RowDatas;
	TSharedPtr<SWeaponListView> ListView;

private:
	TSharedPtr<class SSearchBox> SearchBox;
	FText SearchText;
};
