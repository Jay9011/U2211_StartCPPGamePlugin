#pragma once

#include "CoreMinimal.h"
#include "IDetailCustomization.h"

class WEAPON_API SWeaponDetailsView
	: public IDetailCustomization
{
public:
	static TSharedRef<IDetailCustomization> MakeInstance();
	void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;

public:
	static void OnRefreshByCheckBoxes() { RefreshByCheckBoxes = true; }
	static void OffRefreshByCheckBoxes() { RefreshByCheckBoxes = false; }

private:
	static bool RefreshByCheckBoxes;
};
