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
#include "OcugineAuthModel.generated.h"

//===================================================
//  Ocugine Authenication Models
//===================================================
#pragma region Auth Models
/* Authentication link model */
USTRUCT(BlueprintType) struct FOcugineAuthLinkDataModel
{
	GENERATED_BODY();

	UPROPERTY(EditAnywhere, BlueprintReadOnly) FString auth_url;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FString auth_key;
};
USTRUCT(BlueprintType) struct FOcugineAuthLinkModel : public FOcugineBaseModel { GENERATED_BODY(); UPROPERTY(EditAnywhere, BlueprintReadOnly) FOcugineAuthLinkDataModel data; };

/* Authentication token model */
USTRUCT(BlueprintType) struct FOcugineAuthTokenDataModel
{
	GENERATED_BODY();

	UPROPERTY(EditAnywhere, BlueprintReadOnly) FString access_token;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) TArray<FString> grants;
};
USTRUCT(BlueprintType) struct FOcugineAuthTokenModel : public FOcugineBaseModel { GENERATED_BODY(); UPROPERTY(EditAnywhere, BlueprintReadOnly) FOcugineAuthTokenDataModel data; };
#pragma endregion