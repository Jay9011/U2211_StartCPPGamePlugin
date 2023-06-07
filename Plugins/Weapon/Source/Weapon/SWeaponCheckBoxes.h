#pragma once

#include "CoreMinimal.h"

class WEAPON_API SWeaponCheckBoxes
{
public:
	void AddProperties(TSharedPtr<IPropertyHandle> InHandle);

	TSharedRef<SWidget> Draw(bool bBackground = false);

private:
	TSharedRef<SWidget> DrawCheckBox(int32 InIndex);
	void OnCheckStateChanged(ECheckBoxState InState);

public:
	void DrawProperties(TSharedRef<IPropertyHandle> InPropertyHandle, IDetailChildrenBuilder& InChildrenBuilder);

private:
	struct FInternalData
	{
		bool bChecked;
		FString Name;
		TSharedPtr<IPropertyHandle> Handle;

		FInternalData(TSharedPtr<IPropertyHandle> InHandle)
			: bChecked(false), Handle(InHandle)
		{
			Name = Handle->GetPropertyDisplayName().ToString();
		}
	};
	//IPropertyHandle를 저장하는 배열
	TArray<FInternalData> InternalDatas;
};
