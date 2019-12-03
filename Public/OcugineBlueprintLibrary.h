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

// Ocugine models
#include "OcugineBaseModel.h"
#include "OcugineAuthModel.h"
#include "OcugineUsersModel.h"
#include "OcugineAnalyticsModel.h"
#include "OcugineBackendModel.h"
#include "OcugineGamingModel.h"
#include "OcugineLocaleModel.h"
#include "OcugineReportsModel.h"
#include "OcugineUtilsModel.h"

// Ocugine libraries
#include "CustomGameSettings.h"

// Base libraries
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "Json.h"
#include "JsonUtilities.h"

// Default
#include "OcugineBlueprintLibrary.generated.h"

// Auth delegates
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnGetLinkComplete, const FOcugineAuthLinkModel&, LoginData);
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnGetTokenComplete, const FOcugineAuthTokenModel&, TokenData);
// Locale delegates
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnGetLangComplete, const FOcugineLanguageModel&, LanguageData);
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnGetLangListComplete, const FOcugineLanguagesListModel&, LanguagesListData);
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnGetLocaleComplete, const FOcugineLocaleModel&, LocaleData);
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnGetLocaleListComplete, const FOcugineLocalesListModel&, LocalesListData);
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

	/** Locale Module **/
	// GetLang
	UFUNCTION(BlueprintCallable, Category = "Ocugine|Localization", meta = (AutoCreateRefTerm = "SuccessCallback, ErrorCallback"))
		static void OcugineGetLang(const FString & AppID, const FString & AppKey, const FString & LangCode, const FOnGetLangComplete& SuccessCallback, const FOnError& ErrorCallback);
	static void OcugineGetLang_HttpRequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, FOnGetLangComplete SuccessCallback, FOnError ErrorCallback);
	// GetLangList
	UFUNCTION(BlueprintCallable, Category = "Ocugine|Localization", meta = (AutoCreateRefTerm = "SuccessCallback, ErrorCallback"))
		static void OcugineGetLangList(const FString & AppID, const FString & AppKey, const FOnGetLangListComplete& SuccessCallback, const FOnError& ErrorCallback);
	static void OcugineGetLangList_HttpRequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, FOnGetLangListComplete SuccessCallback, FOnError ErrorCallback);
	// GetLocale
	UFUNCTION(BlueprintCallable, Category = "Ocugine|Localization", meta = (AutoCreateRefTerm = "SuccessCallback, ErrorCallback"))
		static void OcugineGetLocale(const FString & AppID, const FString & AppKey, const FString & LangCode, const FString & LocaleCode, const FOnGetLocaleComplete& SuccessCallback, const FOnError& ErrorCallback);
	static void OcugineGetLocale_HttpRequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, FOnGetLocaleComplete SuccessCallback, FOnError ErrorCallback);
	// GetLocaleList
	UFUNCTION(BlueprintCallable, Category = "Ocugine|Localization", meta = (AutoCreateRefTerm = "SuccessCallback, ErrorCallback"))
		static void OcugineGetLocaleList(const FString & AppID, const FString & AppKey, const FString & Search, const int64 Page, const FOnGetLocaleListComplete& SuccessCallback, const FOnError& ErrorCallback);
	static void OcugineGetLocaleList_HttpRequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, FOnGetLocaleListComplete SuccessCallback, FOnError ErrorCallback);

	/** Utils Module **/
	// Create http request
	static TSharedRef<IHttpRequest> CreateHttpRequest(const FString & Object, const FString & Method, const FString& Content);
	// Get data from file
	UFUNCTION(BlueprintCallable, Category = "Ocugine|Utils")
		static FString GetDataFromFile(FString FileName, bool IsEncoded = false);
	// Save data to file
	UFUNCTION(BlueprintCallable, Category = "Ocugine|Utils")
		static void SaveDataToFile(FString FileName, FString Data);
	// Get grants string from config
	UFUNCTION(BlueprintCallable, Category = "Ocugine|Utils")
		static FString GetGrantsFromConfig();
	// Get language string from config
	UFUNCTION(BlueprintCallable, Category = "Ocugine|Utils")
		static FString GetApplicationLanguageFromConfig();
};