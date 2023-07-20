#pragma once

#include "CoreMinimal.h"
#include "IPropertyTypeCustomization.h"

class WEAPON_API SWeaponEquipmentData
	: public IPropertyTypeCustomization
{
public:
	static TSharedRef<IPropertyTypeCustomization> MakeInstance();
	static TSharedPtr<class SWeaponCheckBoxes> CreateCheckBoxes();

public:
	void CustomizeHeader(TSharedRef<IPropertyHandle> InPropertyHandle, FDetailWidgetRow& InHeaderRow, IPropertyTypeCustomizationUtils& InCustomizationUtils) override;
	void CustomizeChildren(TSharedRef<IPropertyHandle> InPropertyHandle, IDetailChildrenBuilder& InChildBuilder, IPropertyTypeCustomizationUtils& InustomizationUtils) override;

private:
	static TSharedPtr<class SWeaponCheckBoxes> CheckBoxes;
};
