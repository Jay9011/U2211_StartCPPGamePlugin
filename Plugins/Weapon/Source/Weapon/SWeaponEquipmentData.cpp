#include "SWeaponEquipmentData.h"

#include "SWeaponCheckBoxes.h"
#include "DetailWidgetRow.h"
#include "IDetailChildrenBuilder.h"
#include "IDetailPropertyRow.h"
#include "IPropertyUtilities.h"

TSharedPtr<class SWeaponCheckBoxes> SWeaponEquipmentData::CheckBoxes;

TSharedRef<IPropertyTypeCustomization> SWeaponEquipmentData::MakeInstance()
{
	return MakeShareable(new SWeaponEquipmentData());
}

TSharedPtr<SWeaponCheckBoxes> SWeaponEquipmentData::CreateCheckBoxes()
{
	if (CheckBoxes.IsValid())
	{
		CheckBoxes.Reset();
		CheckBoxes = nullptr;
	}

	return CheckBoxes = MakeShareable(new SWeaponCheckBoxes());
}

void SWeaponEquipmentData::CustomizeHeader(TSharedRef<IPropertyHandle> InPropertyHandle, FDetailWidgetRow& InHeaderRow, IPropertyTypeCustomizationUtils& InCustomizationUtils)
{
	FText name = InPropertyHandle->GetPropertyDisplayName();
	
	InHeaderRow
	.NameContent()
	[
		InPropertyHandle->CreatePropertyNameWidget()
	]
	.ValueContent()
	.MinDesiredWidth(FEditorStyle::GetFloat("StandardDialog.MinDesiredSlotWidth"))
	.MaxDesiredWidth(FEditorStyle::GetFloat("StandardDialog.MaxDesiredSlotWidth"))
	[
		CheckBoxes->Draw()
	];
}

void SWeaponEquipmentData::CustomizeChildren(TSharedRef<IPropertyHandle> InPropertyHandle, IDetailChildrenBuilder& InChildBuilder, IPropertyTypeCustomizationUtils& InCustomizationUtils)
{
	CheckBoxes->DrawProperties(InPropertyHandle, InChildBuilder);
}
