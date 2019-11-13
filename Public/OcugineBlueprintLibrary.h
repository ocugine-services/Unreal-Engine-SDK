//  Copyright 2019 Ocugine. All Rights Reserved.
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
#include "OcugineAuthModel.h"
#include "OcugineUsersModel.h"
#include "OcugineAnalyticsModel.h"
#include "OcugineBackendModel.h"
#include "OcugineGamingModel.h"
#include "OcugineLocaleModel.h"
#include "OcugineReportsModel.h"
#include "OcugineUtilsModel.h"

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "Json.h"
#include "JsonUtilities.h"

#include "OcugineBlueprintLibrary.generated.h"

// Auth delegates
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnGetLinkComplete, const FOcugineAuthLinkModel&, LoginData);
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnGetTokenComplete, const FOcugineAuthTokenModel&, TokenData);
// Default Complete delegate
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnComplete, const FOcugineBaseModel&, BaseModel);
// Default Error delegate
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnError, const FString&, Code, const FString&, Description);

UCLASS()
class OCUGINESDK_API UOcugineBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

		/** Fields for requests **/
protected:
	static const FString ServerURL;			// Requests server
public:
	static const FString STATE_OBJECT;
	static const FString OAUTH_OBJECT;
	static const FString USERS_OBJECT;
	static const FString SETTINGS_OBJECT;
	static const FString LOCALE_OBJECT;
	static const FString ANALYTICS_OBJECT;
	static const FString GAMING_OBJECT;
	static const FString CLOUD_OBJECT;
	static const FString REPORTS_OBJECT;
	static const FString UTILS_OBJECT;

	static const FString DEFAULT_PARSE_ERROR;
	static const FString DEFAULT_REQUEST_ERROR;

	/** Auth Module **/
	// Get Link
	UFUNCTION(BlueprintCallable, Category = "Ocugine|Auth", meta = (AutoCreateRefTerm = "SuccessCallback, ErrorCallback"))
		static void OcugineGetLink(const FString& AppID, const FString& AppKey, const FString& Grants, const FOnGetLinkComplete& SuccessCallback, const FOnError& ErrorCallback);
	static void OcugineGetLink_HttpRequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, FOnGetLinkComplete SuccessCallback, FOnError ErrorCallback);
	// Get Token
	UFUNCTION(BlueprintCallable, Category = "Ocugine|Auth", meta = (AutoCreateRefTerm = "SuccessCallback, ErrorCallback"))
		static void OcugineGetToken(const FString& AppID, const FString& AppKey, const FString& AuthKey, const FOnGetTokenComplete& SuccessCallback, const FOnError& ErrorCallback, const bool RememberToken);
	static void OcugineGetToken_HttpRequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, FOnGetTokenComplete SuccessCallback, FOnError ErrorCallback, bool RememberToken);
	// Get Grants
	UFUNCTION(BlueprintCallable, Category = "Ocugine|Auth", meta = (AutoCreateRefTerm = "SuccessCallback, ErrorCallback"))
		static void OcugineGetGrants(const FString& AppID, const FString& AppKey, const FString& AccessToken, const FOnGetTokenComplete& SuccessCallback, const FOnError& ErrorCallback);
	static void OcugineGetGrants_HttpRequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, FOnGetTokenComplete SuccessCallback, FOnError ErrorCallback);
	// Log Out
	UFUNCTION(BlueprintCallable, Category = "Ocugine|Auth", meta = (AutoCreateRefTerm = "SuccessCallback, ErrorCallback"))
		static void OcugineLogout(const FString& AccessToken, const FOnComplete& SuccessCallback, const FOnError& ErrorCallback);
	static void OcugineLogout_HttpRequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, FOnComplete SuccessCallback, FOnError ErrorCallback);

	/** Utils Module **/
	// Create http request
	static TSharedRef<IHttpRequest> CreateHttpRequest(const FString & Object, const FString & Method, const FString& Content);
	// Get data from file
	UFUNCTION(BlueprintCallable, Category = "Ocugine|Utils")
		static FString GetDataFromFile(FString FileName);
	// Save data to file
	UFUNCTION(BlueprintCallable, Category = "Ocugine|Utils")
		static void SaveDataToFile(FString FileName, FString Data);
};