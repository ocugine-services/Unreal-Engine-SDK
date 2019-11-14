//	Copyright 2019 Ocugine. All Rights Reserved.
//  @name           Ocugine SDK
//	@author			Daniel Varentsov <daniel@ocugine.pro>
//  @developer      Ocugine Platform
//  @version        0.7.0
//  @build          700
//  @url            https://ocugine.pro/
//  @docs           https://docs.ocugine.pro/
//  @license        MIT

#pragma once
#include "OcugineBaseModel.generated.h"

//===================================================
//  Ocugine Base Model
//===================================================
#pragma region Base Model
USTRUCT(BlueprintType) struct FOcugineBaseModel
{
	GENERATED_BODY();

	UPROPERTY(EditAnywhere, BlueprintReadOnly) bool complete;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FString message;
};
#pragma endregion

//===================================================
//  Ocugine Enumerators
//===================================================s
#pragma region Enums
// Advanced Field Type
UENUM(BlueprintType) enum EOcugineAdvancedFieldType {
	OAFTTextLine UMETA(DisplayName = "Text Line"),
	OAFTNumber UMETA(DisplayName = "Number"),
	OAFTSelectable UMETA(DisplayName = "Selectable"),
	OAFTMultiselect UMETA(DisplayName = "Multiselect"),
	OAFTTextArea UMETA(DisplayName = "Text Area"),
	OAFTPhone UMETA(DisplayName = "Phone"),
	OAFTEmail UMETA(DisplayName = "Email"),
	OAFTImage UMETA(DisplayName = "Image"),
	OAFTURL UMETA(DisplayName = "URL"),
	OAFTCheckbox UMETA(DisplayName = "Checkbox")
};
UENUM(BlueprintType) enum EOcuginePlatformType {
	OPlTAll UMETA(DisplayName = "All"),
	OPlTAndroid UMETA(DisplayName = "Android"),
	OPlTiOS UMETA(DisplayName = "iOS"),
	OPlTWindowsStandalone UMETA(DisplayName = "Windows (Standalone)"),
	OPlTWindowsUWP UMETA(DisplayName = "Windows (UWP)"),
	OPlTXboxOne UMETA(DisplayName = "Xbox One"),
	OPlTPlaystation4 UMETA(DisplayName = "Playstation 4"),
	OPlTNintendoSwitch UMETA(DisplayName = "Nintendo Switch"),
	OPlTWeb UMETA(DisplayName = "Web"),
	OPlTMacLinux UMETA(DisplayName = "Mac / Linux")
};
UENUM(BlueprintType) enum EOcuginePriorityType {
	OPrTLow UMETA(DisplayName = "Low"),
	OPrTNormal UMETA(DisplayName = "Normal"),
	OPrTHigh UMETA(DisplayName = "High"),
	OPrTVeryHigh UMETA(DisplayName = "Very High")
};
UENUM(BlueprintType) enum EOcugineConfigType {
	OConfText UMETA(DisplayName = "Text"),
	OConfDouble UMETA(DisplayName = "Double"),
	OConfJSON UMETA(DisplayName = "JSON")
};
UENUM(BlueprintType) enum EOcugineOrderType {
	OOrderASC UMETA(DisplayName = "Ascending"),
	OOrderDESC UMETA(DisplayName = "Descending")
};
#pragma endregion