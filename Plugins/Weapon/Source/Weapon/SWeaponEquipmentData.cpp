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
	CheckBoxes->SetUtilities(InCustomizationUtils.GetPropertyUtilities());
	
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
	/*uint32 number = 0;
	InPropertyHandle->GetNumChildren(number);

	for (uint32 i = 0; i < number; i++)
	{
		TSharedPtr<IPropertyHandle> handle = InPropertyHandle->GetChildHandle(i);
		IDetailPropertyRow& row = InChildBuilder.AddProperty(handle.ToSharedRef());

		TSharedPtr<SWidget> name;
		TSharedPtr<SWidget> value;

		row.GetDefaultWidgets(name, value);

		row.CustomWidget()
		.NameContent()
		[
			name.ToSharedRef()
		]
		.ValueContent()
		.MinDesiredWidth(FEditorStyle::GetFloat("StandardDialog.MinDesiredSlotWidth"))
		.MaxDesiredWidth(FEditorStyle::GetFloat("StandardDialog.MaxDesiredSlotWidth"))
		[
			value.ToSharedRef()
		];
	}*/
	
	CheckBoxes->DrawProperties(InPropertyHandle, InChildBuilder);
}
