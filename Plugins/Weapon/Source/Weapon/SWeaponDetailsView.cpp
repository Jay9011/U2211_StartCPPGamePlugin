#include "SWeaponDetailsView.h"

#include "SWeaponCheckBoxes.h"
#include "SWeaponEquipmentData.h"
#include "DetailCategoryBuilder.h"
#include "DetailLayoutBuilder.h"
#include "IDetailPropertyRow.h"
#include "Weapons/CWeaponAsset.h"

TSharedRef<IDetailCustomization> SWeaponDetailsView::MakeInstance()
{
	return MakeShareable(new SWeaponDetailsView());
}

void SWeaponDetailsView::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
	UClass* type = UCWeaponAsset::StaticClass();

	DetailBuilder.HideCategory("CWeaponAsset");

	//ClassSettings 카테고리 추가
	{
		IDetailCategoryBuilder& category = DetailBuilder.EditCategory("ClassSettings", FText::FromString("Class Settings"));
		category.AddProperty("AttachmentClass", type);
		category.AddProperty("EquipmentClass", type);
		category.AddProperty("DoActionClass", type);
	}

	//EquipmentData 카테고리 추가
	{
		IDetailCategoryBuilder& category = DetailBuilder.EditCategory("EquipmentData", FText::FromString("Equipment Data"));
		IDetailPropertyRow& row = category.AddProperty("EquipmentData", type);

		TSharedPtr<SWeaponCheckBoxes> checkBoxes = SWeaponEquipmentData::CreateCheckBoxes();
		checkBoxes->AddProperties(row.GetPropertyHandle());
	}
}
	