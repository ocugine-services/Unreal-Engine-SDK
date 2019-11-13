//	Copyright 2019 Ocugine. All Rights Reserved.
//  @name           Ocugine SDK
//	@author			Daniel Varentsov <daniel@ocugine.pro>
//  @developer      Ocugine Platform
//  @version        0.4.1
//  @build          413
//  @url            https://ocugine.pro/
//  @docs           https://docs.ocugine.pro/
//  @license        MIT

#pragma once

#include "OcugineBaseModel.h"
#include "OcugineLocaleModel.generated.h"

//===================================================
//  Ocugine Localization Models
//===================================================
#pragma region Locale Models

/* Language model */
USTRUCT(BlueprintType) struct FOcugineLanguageDataModel
{
	GENERATED_BODY();
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FString uid;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FString code;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FString name;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FString time;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FString project_id;
};
USTRUCT(BlueprintType) struct FOcugineLanguageModel : public FOcugineBaseModel { GENERATED_BODY(); UPROPERTY(EditAnywhere, BlueprintReadOnly) FOcugineLanguageDataModel data; };
/* Language list model */
USTRUCT(BlueprintType) struct FOcugineLanguageListDataModel { GENERATED_BODY(); UPROPERTY(EditAnywhere, BlueprintReadOnly) TArray<FOcugineLanguageDataModel> list; };
USTRUCT(BlueprintType) struct FOcugineLanguageListModel : public FOcugineBaseModel { GENERATED_BODY(); UPROPERTY(EditAnywhere, BlueprintReadOnly) FOcugineLanguageListDataModel data; };

/* Locale model */
USTRUCT(BlueprintType) struct FOcugineLocaleDataModel
{
	GENERATED_BODY();
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FString uid;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FString code;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FString language;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FString value;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FString project_id;
};
USTRUCT(BlueprintType) struct FOcugineLocaleModel : public FOcugineBaseModel { GENERATED_BODY(); UPROPERTY(EditAnywhere, BlueprintReadOnly) FOcugineLocaleDataModel data; };

/* Locale list model */
USTRUCT(BlueprintType) struct FOcugineLocaleListDataModel
{
	GENERATED_BODY();
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FString lang_name;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) TArray<FOcugineLocaleDataModel> list;
};
USTRUCT(BlueprintType) struct FOcugineLocaleListModel : public FOcugineBaseModel { GENERATED_BODY(); UPROPERTY(EditAnywhere, BlueprintReadOnly) FOcugineLocaleListDataModel data; };

#pragma endregion
