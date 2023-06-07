#include "SWeaponCheckBoxes.h"

#include "WeaponStyle.h"
#include "Widgets/Layout/SUniformGridPanel.h"
#include "IPropertyUtilities.h"
#include "IDetailPropertyRow.h"
#include "IDetailChildrenBuilder.h"
#include "DetailWidgetRow.h"
#include "Chaos/AABB.h"
#include "Chaos/AABB.h"

void SWeaponCheckBoxes::AddProperties(TSharedPtr<IPropertyHandle> InHandle)
{
	uint32 number = 0;
	InHandle->GetNumChildren(number);

	for (uint32 i = 0; i < number; i++)
	{
		InternalDatas.Add(FInternalData(InHandle->GetChildHandle(i)));
	}
}

TSharedRef<SWidget> SWeaponCheckBoxes::Draw(bool bBackground)
{
	TSharedPtr<SUniformGridPanel> panel;
	SAssignNew(panel, SUniformGridPanel);
	panel->SetMinDesiredSlotWidth(150);

	for (int32 i = 0; i < InternalDatas.Num(); i++)
	{
		panel->AddSlot(i, 0)
		[
			DrawCheckBox(i)
		];
	}

	return panel.ToSharedRef();
}

TSharedRef<SWidget> SWeaponCheckBoxes::DrawCheckBox(int32 InIndex)
{
	return SNew(SCheckBox)
	.IsChecked(InternalDatas[InIndex].bChecked)
	.OnCheckStateChanged(this, &SWeaponCheckBoxes::OnCheckStateChanged)
	[
		SNew(STextBlock)
		.Text(FText::FromString(InternalDatas[InIndex].Name))
	];
}

void SWeaponCheckBoxes::OnCheckStateChanged(ECheckBoxState InState)
{
	GLog->Log(StaticEnum<ECheckBoxState>()->GetValueAsString(InState));
}

void SWeaponCheckBoxes::DrawProperties(TSharedRef<IPropertyHandle> InPropertyHandle, IDetailChildrenBuilder& InChildrenBuilder)
{
	uint32 number = 0;
	InPropertyHandle->GetNumChildren(number);

	for (uint32 i = 0; i < number; i++)
	{
		TSharedPtr<IPropertyHandle> handle = InPropertyHandle->GetChildHandle(i);
		IDetailPropertyRow& row = InChildrenBuilder.AddProperty(handle.ToSharedRef());

		TSharedPtr<SWidget> name;
		TSharedPtr<SWidget> value;

		row.GetDefaultWidgets(name, value);

		row.CustomWidget()
		.NameContent()
		[
			name.ToSharedRef()
		]
		.ValueContent()
		.MinDesiredWidth(FWeaponStyle::Get()->DesiredWidth.X)
		.MaxDesiredWidth(FWeaponStyle::Get()->DesiredWidth.Y)
		[
			value.ToSharedRef()
		];
	}
}
