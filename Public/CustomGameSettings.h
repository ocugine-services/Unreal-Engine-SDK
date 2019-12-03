//  Copyright 2019 Ocugine. All Rights Reserved.
//  @name           Ocugine SDK
//	@author			Daniel Varentsov <daniel@ocugine.pro>
//  @developer      Ocugine Platform
//  @version        0.7.0
//  @build          700
//  @url            https://ocugine.pro/
//  @docs           https://docs.ocugine.pro/
//  @license        MIT

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "CustomGameSettings.generated.h"


UENUM(BlueprintType) enum EOcugineConfigLanguageType {
	OLANGen UMETA(DisplayName = "English"),
	OLANGru UMETA(DisplayName = "Russian")
};

USTRUCT(BlueprintType) struct FOcugineConfigGrantsTypes
{
	GENERATED_BODY();

	UPROPERTY(EditAnywhere, BlueprintReadOnly) bool profile;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) bool reports;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) bool payments;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) bool promos;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) bool support_tickets;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) bool reviews;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) bool apps;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) bool leaderboards;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) bool messages;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) bool achivements;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) bool teams;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) bool multiplayer;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) bool social;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) bool cloud_data;
};

/**
* Here you need to setup the most 
* important information about the Project 
* and Project ID / Project Keys. 
*
* You can get your ID and Key here:
* https://cp.ocugine.pro/dashboard/settings/
 */
UCLASS(config = Game, defaultconfig, meta = (DisplayName = "Ocugine Settings")) // default display name would be the class name, ie "Custom Game Settings"
class OCUGINESDK_API UCustomGameSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	/** Application ID */
	UPROPERTY(EditAnywhere, config, Category = "Application Settings" /*, meta = (ConfigRestartRequired = true)*/) FString AppID = "";
	/** Application Key */
	UPROPERTY(EditAnywhere, config, Category = "Application Settings" /*, meta = (ConfigRestartRequired = true)*/) FString AppKey = "";
	/** Grants for application */
	UPROPERTY(EditAnywhere, config, Category = "Application Settings" /*, meta = (ConfigRestartRequired = true)*/) FOcugineConfigGrantsTypes Grants;

	/** Development language */
	UPROPERTY(EditAnywhere, config, Category = "SDK Settings (beta)", meta = (UIMin = 0, ClampMin = 0)) int32 AuthTimeout = 30;
	/** Development language */
	UPROPERTY(EditAnywhere, config, Category = "SDK Settings (beta)") TEnumAsByte<EOcugineConfigLanguageType> Language;

	/// Require reload
	///UPROPERTY(EditAnywhere, config, Category = "Variables", meta = (ConfigRestartRequired = true))
	///float SampleFloatRequireRestart = 0.f;

	/// Min max variable
	///UPROPERTY(config, EditAnywhere, Category = "Variables", meta = (UIMin = 1, ClampMin = 1))
	///int32 ClampedIntSetting = 1;

	/// String array
	///UPROPERTY(config, EditAnywhere, Category = "Variables")
	///TArray<FString> SampleStringList;

	/// Asset reference
	/// UPROPERTY(config, EditAnywhere, Category = "Materials", meta = (AllowedClasses = "MaterialInterface"))
	/// FStringAssetReference StringMaterialAssetReference;

};
