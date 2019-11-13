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
#include "OcugineBackendModel.generated.h"

//===================================================
//  Ocugine Backend Models
//===================================================
#pragma region Backend Models
/* Content list model */
USTRUCT(BlueprintType) struct FOcugineContentListDataListModel
{
	GENERATED_BODY();
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int64 uid;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int64 project_id;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FString content_slug;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int64 time;
};
USTRUCT(BlueprintType) struct FOcugineContentListDataModel { GENERATED_BODY(); UPROPERTY(EditAnywhere, BlueprintReadOnly) TArray<FOcugineContentListDataListModel> list; };
USTRUCT(BlueprintType) struct FOcugineContentListModel : public FOcugineBaseModel { GENERATED_BODY(); UPROPERTY(EditAnywhere, BlueprintReadOnly) FOcugineContentListDataModel data; };

/* Content model */
USTRUCT(BlueprintType) struct FOcugineContentDataInfoModel
{
	GENERATED_BODY();
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int64 uid;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int64 project_id;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FString content_slug;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int64 content_size;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FString content_url;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int64 time;
};
USTRUCT(BlueprintType) struct FOcugineContentDataModel : public FOcugineBaseModel { GENERATED_BODY(); UPROPERTY(EditAnywhere, BlueprintReadOnly) FOcugineContentDataInfoModel info; };
USTRUCT(BlueprintType) struct FOcugineContentModel : public FOcugineBaseModel { GENERATED_BODY(); UPROPERTY(EditAnywhere, BlueprintReadOnly) FOcugineContentDataInfoModel data; };

/* Config model */
USTRUCT(BlueprintType) struct FOcugineConfigDataModel
{
	GENERATED_BODY();
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int64 uid;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FString project_id;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FString name;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FString value;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) TEnumAsByte<EOcugineConfigType> type;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int64 time;
};
USTRUCT(BlueprintType) struct FOcugineConfigModel : public FOcugineBaseModel { GENERATED_BODY(); UPROPERTY(EditAnywhere, BlueprintReadOnly) FOcugineConfigDataModel data; };

/* Configs list model */
USTRUCT(BlueprintType) struct FOcugineConfigsListDataModel { GENERATED_BODY(); UPROPERTY(EditAnywhere, BlueprintReadOnly) TArray<FOcugineConfigDataModel> list; };
USTRUCT(BlueprintType) struct FOcugineConfigsListModel : public FOcugineBaseModel { GENERATED_BODY(); UPROPERTY(EditAnywhere, BlueprintReadOnly) FOcugineConfigsListDataModel data; };

#pragma endregion

