#include "WeaponContextMenu.h"

#include "Weapons/CWeaponAsset.h"

FWeaponContextMenu::FWeaponContextMenu(EAssetTypeCategories::Type InCategory)
{
	Category = InCategory;
}

void FWeaponContextMenu::OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor)
{
   FSimpleAssetEditor::CreateEditor(EToolkitMode::Standalone, EditWithinLevelEditor, InObjects);
}

FText FWeaponContextMenu::GetName() const
{
   return FText::FromString("DataAsset");
}

UClass* FWeaponContextMenu::GetSupportedClass() const
{
   return UCWeaponAsset::StaticClass();
}

FColor FWeaponContextMenu::GetTypeColor() const
{
   return FColor::Blue;
}

uint32 FWeaponContextMenu::GetCategories()
{
   return Category;
}