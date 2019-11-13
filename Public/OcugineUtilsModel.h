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
#include "OcugineUtilsModel.generated.h"

//===================================================
//  Ocugine Utils Models
//===================================================
#pragma region Utils Models

/* API Settings model */
USTRUCT(BlueprintType) struct FOcugineAPISettingsDataInfoModel
{
	GENERATED_BODY();
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int64 uid;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int64 project_id;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) bool enabled;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int64 limitation;
};
USTRUCT(BlueprintType) struct FOcugineAPISettingsDataModel : public FOcugineBaseModel { GENERATED_BODY(); UPROPERTY(EditAnywhere, BlueprintReadOnly) FOcugineAPISettingsDataInfoModel info; };
USTRUCT(BlueprintType) struct FOcugineAPISettingsModel : public FOcugineBaseModel { GENERATED_BODY(); UPROPERTY(EditAnywhere, BlueprintReadOnly) FOcugineAPISettingsDataModel data; };

/* API User Agent info model */
USTRUCT(BlueprintType) struct FOcugineAPIUserAgentDataModel
{
	GENERATED_BODY();
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FString user_agent;
};
USTRUCT(BlueprintType) struct FOcugineAPIUserAgentModel : public FOcugineBaseModel { GENERATED_BODY(); UPROPERTY(EditAnywhere, BlueprintReadOnly) FOcugineAPIUserAgentDataModel data; };

/* API IP info model */
USTRUCT(BlueprintType) struct FOcugineAPIIPDataModel
{
	GENERATED_BODY();
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FString ip;
};
USTRUCT(BlueprintType) struct FOcugineAPIIPModel : public FOcugineBaseModel { GENERATED_BODY(); UPROPERTY(EditAnywhere, BlueprintReadOnly) FOcugineAPIIPDataModel data; };

/* API Device info model */
USTRUCT(BlueprintType) struct FOcugineAPIDeviceDataModel
{
	GENERATED_BODY();
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FString user_device;
};
USTRUCT(BlueprintType) struct FOcugineAPIDeviceModel : public FOcugineBaseModel { GENERATED_BODY(); UPROPERTY(EditAnywhere, BlueprintReadOnly) FOcugineAPIDeviceDataModel data; };

#pragma endregion
