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

#include "OcugineBaseModel.h"
#include "OcugineAnalyticsModel.generated.h"

//===================================================
//  Ocugine Analytics Models
//===================================================
#pragma region Analytics Models
/* Flag Model */
USTRUCT(BlueprintType) struct FOcugineFlagDataModel
{
	GENERATED_BODY();

	UPROPERTY(EditAnywhere, BlueprintReadOnly) FString string;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) bool exists;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int64 time;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int64 counter;
};
USTRUCT(BlueprintType) struct FOcugineFlagModel : public FOcugineBaseModel { GENERATED_BODY(); UPROPERTY(EditAnywhere, BlueprintReadOnly) FOcugineFlagDataModel data; };

/* Flags list model */
USTRUCT(BlueprintType) struct FOcugineFlagsListDataListModel
{
	GENERATED_BODY();

	UPROPERTY(EditAnywhere, BlueprintReadOnly) bool complete;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) TArray<FString> list;
};
USTRUCT(BlueprintType) struct FOcugineFlagsListDataModel { GENERATED_BODY(); UPROPERTY(EditAnywhere, BlueprintReadOnly) TArray<FOcugineFlagsListDataListModel> list; };
USTRUCT(BlueprintType) struct FOcugineFlagsListModel : public FOcugineBaseModel { GENERATED_BODY(); UPROPERTY(EditAnywhere, BlueprintReadOnly) FOcugineFlagsListDataModel data; };

/* LatestFlags list model */
USTRUCT(BlueprintType) struct FOcugineLatestFlagsListDataListModel
{
	GENERATED_BODY();

	UPROPERTY(EditAnywhere, BlueprintReadOnly) int64 project_id;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int64 profile_uid;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FString flag;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FString viewer;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int64 time;
};
USTRUCT(BlueprintType) struct FOcugineLatestFlagsListDataModel { GENERATED_BODY(); UPROPERTY(EditAnywhere, BlueprintReadOnly) TArray<FOcugineLatestFlagsListDataListModel> list; };
USTRUCT(BlueprintType) struct FOcugineLatestFlagsListModel : public FOcugineBaseModel { GENERATED_BODY(); UPROPERTY(EditAnywhere, BlueprintReadOnly) FOcugineLatestFlagsListDataModel data; };

#pragma endregion