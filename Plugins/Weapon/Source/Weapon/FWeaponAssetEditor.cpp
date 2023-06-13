#include "FWeaponAssetEditor.h"

#include "Weapons/CWeaponAsset.h"
#include "SWeaponLeftArea.h"
#include "SWeaponDetailsView.h"
#include "SWeaponDoActionData.h"
#include "SWeaponEquipmentData.h"
#include "SWeaponHitData.h"

const FName FWeaponAssetEditor::EditorName	  = "WeaponAssetEditor";
const FName FWeaponAssetEditor::LeftAreaTabId = "ListView";
const FName FWeaponAssetEditor::DetailTabId	  = "Details";

TSharedPtr<FWeaponAssetEditor> FWeaponAssetEditor::Instance = nullptr;

void FWeaponAssetEditor::OpenWindow(FString InAssetName)
{
	if (Instance.IsValid())
	{
		if (Instance->LeftArea.IsValid())
		{
			FWeaponRowDataPtr ptr = nullptr;
		
			if(InAssetName.Len() > 0)
				ptr = Instance->LeftArea->GetRowDataPtrByName(InAssetName);
		
			if(ptr.IsValid() == false)
				ptr = Instance->LeftArea->GetFirstDataPtr();
		
			Instance->LeftArea->SelectDataPtr(ptr->Asset);
		
			return;
		}
		
		Instance->CloseWindow();

		Instance.Reset();
		Instance = nullptr;
	}

	Instance = MakeShareable(new FWeaponAssetEditor());
	Instance->Open(InAssetName);
}

void FWeaponAssetEditor::Shutdown()
{
	if (Instance.IsValid())
	{
		Instance->CloseWindow();

		Instance.Reset();
		Instance = nullptr;
	}
}

void FWeaponAssetEditor::Open(FString InAssetName)
{
	LeftArea = SNew(SWeaponLeftArea)
	.OnWeaponListViewSelectedItem(this, &FWeaponAssetEditor::OnListViewSelectedItem);

	FPropertyEditorModule& prop = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");

	//DetailsView
	{
		FDetailsViewArgs args(false, false, true, FDetailsViewArgs::ObjectsUseNameArea);
		args.ViewIdentifier = "WeaponAssetEditorDetailsView";
		DetailsView = prop.CreateDetailView(args);

		FOnGetDetailCustomizationInstance detailsView;
		detailsView.BindStatic(&SWeaponDetailsView::MakeInstance);
		DetailsView->SetGenericLayoutDetailsDelegate(detailsView);
	}

	//EquipmentData
	{
		FOnGetPropertyTypeCustomizationInstance instance;
		instance.BindStatic(&SWeaponEquipmentData::MakeInstance);
		prop.RegisterCustomPropertyTypeLayout("EquipmentData", instance);
	}

	//DoActionData
	{
		FOnGetPropertyTypeCustomizationInstance instance;
		instance.BindStatic(&SWeaponDoActionData::MakeInstance);
		prop.RegisterCustomPropertyTypeLayout("DoActionData", instance);
	}
	
	//HitData
	{
		FOnGetPropertyTypeCustomizationInstance instance;
		instance.BindStatic(&SWeaponHitData::MakeInstance);
		prop.RegisterCustomPropertyTypeLayout("HitData", instance);
	}

	TSharedRef<FTabManager::FLayout> Layout = FTabManager::NewLayout("WeaponAssetEditor_Layout")
	->AddArea
	(
		//주 영역 설정
		FTabManager::NewPrimaryArea()
		//주 영역을 가로로 분할함
		->SetOrientation(Orient_Vertical)
		->Split
		(
			FTabManager::NewStack()
			->SetSizeCoefficient(0.1f)
			->AddTab(GetToolbarTabId(), ETabState::OpenedTab)
		)
		->Split
		(
			//영역 크기 조절 가능한 Splitter
			FTabManager::NewSplitter()
			->SetOrientation(Orient_Horizontal)
			//첫 번째 영역
			->Split
			(
				FTabManager::NewStack()
				->SetSizeCoefficient(0.175f)
				->AddTab(LeftAreaTabId, ETabState::OpenedTab)
				->SetHideTabWell(true)
			)
			//두 번째 영역
			->Split
			(
				FTabManager::NewStack()
				->SetSizeCoefficient(0.725f)
				->AddTab(DetailTabId, ETabState::OpenedTab)
				->SetHideTabWell(true)
			)
		)
	);

	UCWeaponAsset* asset = nullptr;
	if (InAssetName.Len() > 0)
	{
		FWeaponRowDataPtr ptr = LeftArea->GetRowDataPtrByName(InAssetName);

		if(LeftArea->SelectedRowDataPtrName() == InAssetName)
			return;

		if(ptr.IsValid() == false)
			asset = LeftArea->GetFirstDataPtr()->Asset;
		else
			asset = ptr->Asset;
	}
	else
	{
		asset = LeftArea->GetFirstDataPtr()->Asset;
	}

	// UCWeaponAsset* asset = NewObject<UCWeaponAsset>();
	FAssetEditorToolkit::InitAssetEditor(EToolkitMode::Standalone, TSharedPtr<IToolkitHost>(), EditorName, Layout, true, true, asset);

	// DetailsView->SetObject(asset);
	LeftArea->SelectDataPtr(asset);
}

bool FWeaponAssetEditor::OnRequestClose()
{
	if (!!DetailsView)
	{
		// 만약 Geditor(현재 열려있는 에디터)가 존재하고, AssetEditorSubsystem이 존재한다면
		if (!!GEditor && !!GEditor->GetEditorSubsystem<UAssetEditorSubsystem>())
			// AssetEditorSubsystem에게 AssetEditor가 닫힌 것을 알림
			GEditor->GetEditorSubsystem<UAssetEditorSubsystem>()->NotifyAssetClosed(GetEditingObject(), this);

		if (FModuleManager::Get().IsModuleLoaded("PropertyEditor"))
		{
			FPropertyEditorModule& prop = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
			prop.UnregisterCustomPropertyTypeLayout("EquipmentData");
			prop.UnregisterCustomPropertyTypeLayout("DoActionData");
			prop.UnregisterCustomPropertyTypeLayout("HitData");
		}
	}

	if (LeftArea.IsValid())
		LeftArea.Reset();

	if (DetailsView.IsValid())
		DetailsView.Reset();

	return true;
}

void FWeaponAssetEditor::RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	FAssetEditorToolkit::RegisterTabSpawners(InTabManager);

	FOnSpawnTab tab;
	tab.BindSP(this, &FWeaponAssetEditor::Spawn_LeftAreaTab);
	TabManager->RegisterTabSpawner(LeftAreaTabId, tab);

	FOnSpawnTab tab2;
	tab2.BindSP(this, &FWeaponAssetEditor::Spawn_DetailsViewTab);
	TabManager->RegisterTabSpawner(DetailTabId, tab2);
}

TSharedRef<SDockTab> FWeaponAssetEditor::Spawn_LeftAreaTab(const FSpawnTabArgs& InArgs)
{
	// 원형 Slate 문법
	// TSharedPtr<STextBlock> tb =
	// 	SNew(STextBlock)
	// 	.Text(FText::FromString("Test"));
	//
	// TSharedPtr<SDockTab> tab =
	// 	SNew(SDockTab)
	// 	.Content()
	// 	[
	// 		tb.ToSharedRef()
	// 	];
	//
	// return tab.ToSharedRef();

	// Slate 문법
	// return SNew(SDockTab)
	// 	   [
	// 		   SNew(SButton)
	// 		   .OnClicked(this, &FWeaponAssetEditor::OnClicked)
	// 		   [
	// 			   SNew(STextBlock)
	// 			   .Text(FText::FromString("Click"))
	// 		   ]
	// 	   ];

	return SNew(SDockTab)
	[
		LeftArea.ToSharedRef()
	];
}

TSharedRef<SDockTab> FWeaponAssetEditor::Spawn_DetailsViewTab(const FSpawnTabArgs& InArgs)
{
	return SNew(SDockTab)
	[
		DetailsView.ToSharedRef()
	];
}

FName FWeaponAssetEditor::GetToolkitFName() const
{
	return EditorName;
}

FText FWeaponAssetEditor::GetBaseToolkitName() const
{
	return FText::FromName(EditorName);
}

FString FWeaponAssetEditor::GetWorldCentricTabPrefix() const
{
	return EditorName.ToString();
}

FLinearColor FWeaponAssetEditor::GetWorldCentricTabColorScale() const
{
	return FLinearColor(0, 0, 1);
}

FReply FWeaponAssetEditor::OnClicked()
{
	GLog->Log("Test");

	return FReply::Handled();
}

void FWeaponAssetEditor::OnListViewSelectedItem(FWeaponRowDataPtr InPtr)
{
	if(InPtr == nullptr)
		return;

	// 현재 편집중인 객체가 존재한다면
	if(!!GetEditingObject())
		// 편집중인 객체를 제거해야 충돌이 발생하지 않음
		RemoveEditingObject(GetEditingObject());

	// InPtr 로 받은 객체를 편집중인 객체로 설정
	AddEditingObject(InPtr->Asset);
	// 편집중인 객체를 DetailsView에 설정
	DetailsView->SetObject(InPtr->Asset);
}