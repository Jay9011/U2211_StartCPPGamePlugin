#pragma once

#include "CoreMinimal.h"
#include "IDetailCustomization.h"

class WEAPON_API SWeaponDetailsView
	: public IDetailCustomization
{
public:
	static TSharedRef<IDetailCustomization> MakeInstance();
	virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;
	
private:
	static bool RefreshByCheckBoxes;
	
/* 
 * Getters / Setters
 */
public:
	static void OnRefreshByCheckBoxes() { RefreshByCheckBoxes = true; }
	static void OffRefreshByCheckBoxes() { RefreshByCheckBoxes = false; }
};
