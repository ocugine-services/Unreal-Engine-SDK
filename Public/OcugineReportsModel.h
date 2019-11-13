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
#include "OcugineReportsModel.generated.h"

//===================================================
//  Ocugine Performance Models
//===================================================
#pragma region Performance Models

/* Error Report model */
USTRUCT(BlueprintType) struct FOcugineErrorReportDataModel
{
	GENERATED_BODY();
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int64 uid;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FString project_id;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FString title;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FString code;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FString body;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FString platform;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) bool critical;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int64 time;
};
USTRUCT(BlueprintType) struct FOcugineErrorReportModel : public FOcugineBaseModel { GENERATED_BODY(); UPROPERTY(EditAnywhere, BlueprintReadOnly) FOcugineErrorReportDataModel data; };

#pragma endregion
