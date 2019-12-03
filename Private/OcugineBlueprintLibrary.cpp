//  Copyright 2019 Ocugine. All Rights Reserved.
//  @name           Ocugine SDK
//	@author			Daniel Varentsov <daniel@ocugine.pro>
//  @developer      Ocugine Platform
//  @version        0.7.0
//  @build          700
//  @url            https://ocugine.pro/
//  @docs           https://docs.ocugine.pro/
//  @license        MIT

#include "OcugineBlueprintLibrary.h"
#include "Misc/Base64.h"

// Server URL
const FString UOcugineBlueprintLibrary::ServerURL(TEXT("https://cp.ocugine.pro/api/"));

// Objects
const FString UOcugineBlueprintLibrary::STATE_OBJECT(TEXT("state"));
const FString UOcugineBlueprintLibrary::OAUTH_OBJECT(TEXT("oauth"));
const FString UOcugineBlueprintLibrary::USERS_OBJECT(TEXT("users"));
const FString UOcugineBlueprintLibrary::SETTINGS_OBJECT(TEXT("api_settings"));
const FString UOcugineBlueprintLibrary::LOCALE_OBJECT(TEXT("localization"));
const FString UOcugineBlueprintLibrary::ANALYTICS_OBJECT(TEXT("analytics"));
const FString UOcugineBlueprintLibrary::GAMING_OBJECT(TEXT("gaming"));
const FString UOcugineBlueprintLibrary::CLOUD_OBJECT(TEXT("cloud"));
const FString UOcugineBlueprintLibrary::REPORTS_OBJECT(TEXT("reports"));
const FString UOcugineBlueprintLibrary::UTILS_OBJECT(TEXT("utils"));

// Errors
const FString UOcugineBlueprintLibrary::DEFAULT_PARSE_ERROR(TEXT("Failed to parse server response. Please, try again later or contact with game administration."));
const FString UOcugineBlueprintLibrary::DEFAULT_REQUEST_ERROR(TEXT("Failed to send request at the Ocugine server. Please, check your internet connection and try again."));

//===================================================
//  Ocugine Unteal Engine 4 SDK Authentication
//===================================================
#pragma region Auth
//============================================================
//  @method     GetLink()
//  @type       Static Void with delegates
//  @usage      Get OAuth link
//  @args       (FString) AppID - Application ID
//				(FString) AppKey - Application Key
//				(FString) Grants - Application Grants
//              (delegate) SuccessCallback - Complete Callback
//              (delegate) ErrorCallback - Error Callback
//============================================================
void UOcugineBlueprintLibrary::OcugineGetLink(const FString & AppID, const FString & AppKey, const FString & Grants, const FOnGetLinkComplete & SuccessCallback, const FOnError & ErrorCallback)
{
	const FString PostContent = FString::Printf(TEXT("app_id=%s&app_key=%s&grants=%s&lang=%s"),
		AppID != "" ? *AppID : *GetDefault<UCustomGameSettings>()->AppID,
		AppKey != "" ? *AppKey : *GetDefault<UCustomGameSettings>()->AppKey,
		Grants != "" ? *Grants : *UOcugineBlueprintLibrary::GetGrantsFromConfig(),
		*UOcugineBlueprintLibrary::GetApplicationLanguageFromConfig()
	);

	TSharedRef<IHttpRequest> HttpRequest = UOcugineBlueprintLibrary::CreateHttpRequest(UOcugineBlueprintLibrary::OAUTH_OBJECT, "get_link", PostContent);
	HttpRequest->OnProcessRequestComplete().BindStatic(&UOcugineBlueprintLibrary::OcugineGetLink_HttpRequestComplete, SuccessCallback, ErrorCallback);
	HttpRequest->ProcessRequest();
}
void UOcugineBlueprintLibrary::OcugineGetLink_HttpRequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, FOnGetLinkComplete SuccessCallback, FOnError ErrorCallback)
{
	if (bSucceeded) {																									// If request succeeded
		FString ResponseStr = HttpResponse->GetContentAsString(); FOcugineAuthLinkModel ConvertedResponse;						// Declare temp objects
		if (FJsonObjectConverter::JsonObjectStringToUStruct<FOcugineAuthLinkModel>(ResponseStr, &ConvertedResponse, 0, 0))		// If converted
		{
			if (ConvertedResponse.complete) { SuccessCallback.ExecuteIfBound(ConvertedResponse); }						// Execute callback if complete is true
			else { ErrorCallback.ExecuteIfBound(TEXT("Ocugine Error"), ConvertedResponse.message); }					// If not completed
		}
		else { ErrorCallback.ExecuteIfBound(TEXT("Parse error"), DEFAULT_PARSE_ERROR); }								// If convert exception
	}
	else { ErrorCallback.ExecuteIfBound(TEXT("Request error"), DEFAULT_REQUEST_ERROR); }								// If request exception
}

//============================================================
//  @method     GetToken()
//  @type       Static Void with delegates
//  @usage      Get user token
//  @args       (FString) AppID - Application ID
//				(FString) AppKey - Application Key
//				(FString) AuthKey - Auth key from get link
//              (delegate) SuccessCallback - Complete Callback
//              (delegate) ErrorCallback - Error Callback
//============================================================
void UOcugineBlueprintLibrary::OcugineGetToken(const FString & AppID, const FString & AppKey, const FString & AuthKey, const FOnGetTokenComplete & SuccessCallback, const FOnError & ErrorCallback, const bool RememberToken)
{
	// If token exist in directory
	if (RememberToken && !UOcugineBlueprintLibrary::GetDataFromFile("access_token.o").IsEmpty()) {
		FOcugineAuthTokenModel tempdata = FOcugineAuthTokenModel();
		tempdata.message = "Cached token returned";
		tempdata.complete = true;
		FBase64::Decode(UOcugineBlueprintLibrary::GetDataFromFile("access_token.o"), tempdata.data.access_token);
		SuccessCallback.ExecuteIfBound(tempdata);
	}
	else {
		const FString PostContent = FString::Printf(TEXT("app_id=%s&app_key=%s&auth_key=%s"),
			AppID != "" ? *AppID : *GetDefault<UCustomGameSettings>()->AppID,
			AppKey != "" ? *AppKey : *GetDefault<UCustomGameSettings>()->AppKey,
			*AuthKey
		);
		TSharedRef<IHttpRequest> HttpRequest = UOcugineBlueprintLibrary::CreateHttpRequest(UOcugineBlueprintLibrary::OAUTH_OBJECT, "get_token", PostContent);
		HttpRequest->OnProcessRequestComplete().BindStatic(&UOcugineBlueprintLibrary::OcugineGetToken_HttpRequestComplete, SuccessCallback, ErrorCallback, RememberToken);
		HttpRequest->ProcessRequest();
	}
}
void UOcugineBlueprintLibrary::OcugineGetToken_HttpRequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, FOnGetTokenComplete SuccessCallback, FOnError ErrorCallback, bool RememberToken)
{
	if (bSucceeded) {																									// If request succeeded
		FString ResponseStr = HttpResponse->GetContentAsString(); FOcugineAuthTokenModel ConvertedResponse;					// Declare temp objects
		if (FJsonObjectConverter::JsonObjectStringToUStruct<FOcugineAuthTokenModel>(ResponseStr, &ConvertedResponse, 0, 0))	// If converted
		{
			if (ConvertedResponse.complete)																				// If complete is true
			{
				if (RememberToken) { UOcugineBlueprintLibrary::SaveDataToFile("access_token.o", FBase64::Encode(ConvertedResponse.data.access_token)); }
				SuccessCallback.ExecuteIfBound(ConvertedResponse);
			}
			else { ErrorCallback.ExecuteIfBound(TEXT("Ocugine Error"), ConvertedResponse.message); }					// If not completed
		}
		else { ErrorCallback.ExecuteIfBound(TEXT("Parse error"), DEFAULT_PARSE_ERROR); }								// If convert exception
	}
	else { ErrorCallback.ExecuteIfBound(TEXT("Request error"), DEFAULT_REQUEST_ERROR); }								// If request exception
}

//============================================================
//  @method     GetGrants()
//  @type       Static Void with delegates
//  @usage      Get user grants data
//  @args       (FString) AppID - Application ID
//				(FString) AppKey - Application Key
//				(FString) AccessToken - Access token
//              (delegate) SuccessCallback - Complete Callback
//              (delegate) ErrorCallback - Error Callback
//============================================================
void UOcugineBlueprintLibrary::OcugineGetGrants(const FString & AppID, const FString & AppKey, const FString & AccessToken, const FOnGetTokenComplete & SuccessCallback, const FOnError & ErrorCallback)
{
	const FString PostContent = FString::Printf(TEXT("app_id=%s&app_key=%s&access_token=%s"),
		AppID != "" ? *AppID : *GetDefault<UCustomGameSettings>()->AppID,
		AppKey != "" ? *AppKey : *GetDefault<UCustomGameSettings>()->AppKey,
		AccessToken != "" ? *AccessToken : *UOcugineBlueprintLibrary::GetDataFromFile("access_token.o", true)
	);

	TSharedRef<IHttpRequest> HttpRequest = UOcugineBlueprintLibrary::CreateHttpRequest(UOcugineBlueprintLibrary::OAUTH_OBJECT, "get_grants", PostContent);
	HttpRequest->OnProcessRequestComplete().BindStatic(&UOcugineBlueprintLibrary::OcugineGetGrants_HttpRequestComplete, SuccessCallback, ErrorCallback);
	HttpRequest->ProcessRequest();
}
void UOcugineBlueprintLibrary::OcugineGetGrants_HttpRequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, FOnGetTokenComplete SuccessCallback, FOnError ErrorCallback)
{
	if (bSucceeded) {																									// If request succeeded
		FString ResponseStr = HttpResponse->GetContentAsString(); FOcugineAuthTokenModel ConvertedResponse;					// Declare temp objects
		if (FJsonObjectConverter::JsonObjectStringToUStruct<FOcugineAuthTokenModel>(ResponseStr, &ConvertedResponse, 0, 0))	// If converted
		{
			if (ConvertedResponse.complete) { SuccessCallback.ExecuteIfBound(ConvertedResponse); }						// If complete is true execute callback
			else { ErrorCallback.ExecuteIfBound(TEXT("Ocugine Error"), ConvertedResponse.message); }					// If not completed
		}
		else { ErrorCallback.ExecuteIfBound(TEXT("Parse error"), DEFAULT_PARSE_ERROR); }								// If convert exception
	}
	else { ErrorCallback.ExecuteIfBound(TEXT("Request error"), DEFAULT_REQUEST_ERROR); }								// If request exception
}

//============================================================
//  @method     Logout()
//  @type       Static Void with delegates
//  @usage      Logout from ocugine
//  @args       (FString) AccessToken - Access token
//              (delegate) SuccessCallback - Complete Callback
//              (delegate) ErrorCallback - Error Callback
//============================================================
void UOcugineBlueprintLibrary::OcugineLogout(const FString& AccessToken, const FOnComplete & SuccessCallback, const FOnError & ErrorCallback)
{
	const FString PostContent = FString::Printf(TEXT("access_token=%s"),
		AccessToken != "" ? *AccessToken : *UOcugineBlueprintLibrary::GetDataFromFile("access_token.o", true)
	);

	TSharedRef<IHttpRequest> HttpRequest = UOcugineBlueprintLibrary::CreateHttpRequest(UOcugineBlueprintLibrary::OAUTH_OBJECT, "logout", PostContent);
	HttpRequest->OnProcessRequestComplete().BindStatic(&UOcugineBlueprintLibrary::OcugineLogout_HttpRequestComplete, SuccessCallback, ErrorCallback);
	HttpRequest->ProcessRequest();
}
void UOcugineBlueprintLibrary::OcugineLogout_HttpRequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, FOnComplete SuccessCallback, FOnError ErrorCallback)
{
	if (bSucceeded) {																									// If request succeeded
		FString ResponseStr = HttpResponse->GetContentAsString(); FOcugineBaseModel ConvertedResponse;					// Declare temp objects
		if (FJsonObjectConverter::JsonObjectStringToUStruct<FOcugineBaseModel>(ResponseStr, &ConvertedResponse, 0, 0))	// If converted
		{
			if (ConvertedResponse.complete) {																			// If complete
				SuccessCallback.ExecuteIfBound(ConvertedResponse);														// Execute callback
			}
			else { ErrorCallback.ExecuteIfBound(TEXT("Ocugine Error"), ConvertedResponse.message); }					// If not completed
			UOcugineBlueprintLibrary::SaveDataToFile("access_token.o", "");												// Clear token anyways
		}
		else { ErrorCallback.ExecuteIfBound(TEXT("Parse error"), DEFAULT_PARSE_ERROR); }								// If convert exception
	}
	else { ErrorCallback.ExecuteIfBound(TEXT("Request error"), DEFAULT_REQUEST_ERROR); }								// If request exception
}
#pragma endregion

//===================================================
//  Ocugine Unteal Engine 4 SDK Analytics Module
//===================================================
#pragma region Analytics

#pragma endregion

//===================================================
//  Ocugine Unteal Engine 4 SDK Backend Module
//===================================================
#pragma region Backend

#pragma endregion

//===================================================
//  Ocugine Unteal Engine 4 SDK Game Services Module
//===================================================
#pragma region Gaming

#pragma endregion

//===================================================
//  Ocugine Unteal Engine 4 SDK Notifications Module
//===================================================
#pragma region Notifications

#pragma endregion

//===================================================
//  Ocugine Unteal Engine 4 SDK Localization Module
//===================================================
#pragma region Localization
void UOcugineBlueprintLibrary::OcugineGetLang(const FString & AppID, const FString & AppKey, const FString & LangCode, const FOnGetLangComplete &SuccessCallback, const FOnError &ErrorCallback)
{
	const FString PostContent = FString::Printf(TEXT("app_id=%s&app_key=%s&code=%s"),
		AppID != "" ? *AppID : *GetDefault<UCustomGameSettings>()->AppID,
		AppKey != "" ? *AppKey : *GetDefault<UCustomGameSettings>()->AppKey,
		*LangCode
	);

	TSharedRef<IHttpRequest> HttpRequest = UOcugineBlueprintLibrary::CreateHttpRequest(UOcugineBlueprintLibrary::LOCALE_OBJECT, "get_lang", PostContent);
	HttpRequest->OnProcessRequestComplete().BindStatic(&UOcugineBlueprintLibrary::OcugineGetLang_HttpRequestComplete, SuccessCallback, ErrorCallback);
	HttpRequest->ProcessRequest();
}
void UOcugineBlueprintLibrary::OcugineGetLang_HttpRequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, FOnGetLangComplete SuccessCallback, FOnError ErrorCallback)
{
	if (bSucceeded)
	{ // If request succeeded
		FString ResponseStr = HttpResponse->GetContentAsString(); FOcugineLanguageModel ConvertedResponse; // Declare temp objects
		if (FJsonObjectConverter::JsonObjectStringToUStruct<FOcugineLanguageModel>(ResponseStr, &ConvertedResponse, 0, 0)) // If converted
		{
			if (ConvertedResponse.complete) { SuccessCallback.ExecuteIfBound(ConvertedResponse); } // If complete is true execute callback
			else { ErrorCallback.ExecuteIfBound(TEXT("Ocugine Error"), ConvertedResponse.message); } // If not completed
		}
		else { ErrorCallback.ExecuteIfBound(TEXT("Parse error"), DEFAULT_PARSE_ERROR); } // If convert exception
	}
	else { ErrorCallback.ExecuteIfBound(TEXT("Request error"), DEFAULT_REQUEST_ERROR); } // If request exception
};

void UOcugineBlueprintLibrary::OcugineGetLangList(const FString & AppID, const FString & AppKey, const FOnGetLangListComplete &SuccessCallback, const FOnError &ErrorCallback)
{
	const FString PostContent = FString::Printf(TEXT("app_id=%s&app_key=%s"),
		AppID != "" ? *AppID : *GetDefault<UCustomGameSettings>()->AppID,
		AppKey != "" ? *AppKey : *GetDefault<UCustomGameSettings>()->AppKey
	);

	TSharedRef<IHttpRequest> HttpRequest = UOcugineBlueprintLibrary::CreateHttpRequest(UOcugineBlueprintLibrary::LOCALE_OBJECT, "get_lang_list", PostContent);
	HttpRequest->OnProcessRequestComplete().BindStatic(&UOcugineBlueprintLibrary::OcugineGetLangList_HttpRequestComplete, SuccessCallback, ErrorCallback);
	HttpRequest->ProcessRequest();
}
void UOcugineBlueprintLibrary::OcugineGetLangList_HttpRequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, FOnGetLangListComplete SuccessCallback, FOnError ErrorCallback)
{
	if (bSucceeded)
	{ // If request succeeded
		FString ResponseStr = HttpResponse->GetContentAsString(); FOcugineLanguagesListModel ConvertedResponse; // Declare temp objects
		if (FJsonObjectConverter::JsonObjectStringToUStruct<FOcugineLanguagesListModel>(ResponseStr, &ConvertedResponse, 0, 0)) // If converted
		{
			if (ConvertedResponse.complete) { SuccessCallback.ExecuteIfBound(ConvertedResponse); } // If complete is true execute callback
			else { ErrorCallback.ExecuteIfBound(TEXT("Ocugine Error"), ConvertedResponse.message); } // If not completed
		}
		else { ErrorCallback.ExecuteIfBound(TEXT("Parse error"), DEFAULT_PARSE_ERROR); } // If convert exception
	}
	else { ErrorCallback.ExecuteIfBound(TEXT("Request error"), DEFAULT_REQUEST_ERROR); } // If request exception
};

void UOcugineBlueprintLibrary::OcugineGetLocale(const FString & AppID, const FString & AppKey, const FString & LangCode, const FString & LocaleCode, const FOnGetLocaleComplete &SuccessCallback, const FOnError &ErrorCallback)
{
	const FString PostContent = FString::Printf(TEXT("app_id=%s&app_key=%s&lang=%s&code=%s"),
		AppID != "" ? *AppID : *GetDefault<UCustomGameSettings>()->AppID,
		AppKey != "" ? *AppKey : *GetDefault<UCustomGameSettings>()->AppKey,
		*LangCode,
		*LocaleCode
	);

	TSharedRef<IHttpRequest> HttpRequest = UOcugineBlueprintLibrary::CreateHttpRequest(UOcugineBlueprintLibrary::LOCALE_OBJECT, "get_locale", PostContent);
	HttpRequest->OnProcessRequestComplete().BindStatic(&UOcugineBlueprintLibrary::OcugineGetLocale_HttpRequestComplete, SuccessCallback, ErrorCallback);
	HttpRequest->ProcessRequest();
}
void UOcugineBlueprintLibrary::OcugineGetLocale_HttpRequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, FOnGetLocaleComplete SuccessCallback, FOnError ErrorCallback)
{
	if (bSucceeded)
	{ // If request succeeded
		FString ResponseStr = HttpResponse->GetContentAsString(); FOcugineLocaleModel ConvertedResponse; // Declare temp objects
		if (FJsonObjectConverter::JsonObjectStringToUStruct<FOcugineLocaleModel>(ResponseStr, &ConvertedResponse, 0, 0)) // If converted
		{
			if (ConvertedResponse.complete) { SuccessCallback.ExecuteIfBound(ConvertedResponse); } // If complete is true execute callback
			else { ErrorCallback.ExecuteIfBound(TEXT("Ocugine Error"), ConvertedResponse.message); } // If not completed
		}
		else { ErrorCallback.ExecuteIfBound(TEXT("Parse error"), DEFAULT_PARSE_ERROR); } // If convert exception
	}
	else { ErrorCallback.ExecuteIfBound(TEXT("Request error"), DEFAULT_REQUEST_ERROR); } // If request exception
};

void UOcugineBlueprintLibrary::OcugineGetLocaleList(const FString & AppID, const FString & AppKey, const FString & Search, const int64 Page, const FOnGetLocaleListComplete &SuccessCallback, const FOnError &ErrorCallback)
{
	const FString PostContent = FString::Printf(TEXT("app_id=%s&app_key=%s&search=%s&page=%s"),
		AppID != "" ? *AppID : *GetDefault<UCustomGameSettings>()->AppID,
		AppKey != "" ? *AppKey : *GetDefault<UCustomGameSettings>()->AppKey,
		*Search,
		*FString::FromInt(Page)
	);

	TSharedRef<IHttpRequest> HttpRequest = UOcugineBlueprintLibrary::CreateHttpRequest(UOcugineBlueprintLibrary::LOCALE_OBJECT, "get_locale_list", PostContent);
	HttpRequest->OnProcessRequestComplete().BindStatic(&UOcugineBlueprintLibrary::OcugineGetLocaleList_HttpRequestComplete, SuccessCallback, ErrorCallback);
	HttpRequest->ProcessRequest();
}
void UOcugineBlueprintLibrary::OcugineGetLocaleList_HttpRequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, FOnGetLocaleListComplete SuccessCallback, FOnError ErrorCallback)
{
	if (bSucceeded)
	{ // If request succeeded
		FString ResponseStr = HttpResponse->GetContentAsString(); FOcugineLocalesListModel ConvertedResponse; // Declare temp objects
		if (FJsonObjectConverter::JsonObjectStringToUStruct<FOcugineLocalesListModel>(ResponseStr, &ConvertedResponse, 0, 0)) // If converted
		{
			if (ConvertedResponse.complete) { SuccessCallback.ExecuteIfBound(ConvertedResponse); } // If complete is true execute callback
			else { ErrorCallback.ExecuteIfBound(TEXT("Ocugine Error"), ConvertedResponse.message); } // If not completed
		}
		else { ErrorCallback.ExecuteIfBound(TEXT("Parse error"), DEFAULT_PARSE_ERROR); } // If convert exception
	}
	else { ErrorCallback.ExecuteIfBound(TEXT("Request error"), DEFAULT_REQUEST_ERROR); } // If request exception
};

#pragma endregion

//===================================================
//  Ocugine Unteal Engine 4 SDK Marketing Module
//===================================================
#pragma region Marketing

#pragma endregion

//===================================================
//  Ocugine Unteal Engine 4 SDK Monetizaion Module
//===================================================
#pragma region Monetizaion

#pragma endregion

//===================================================
//  Ocugine Unteal Engine 4 SDK Performance Module
//===================================================
#pragma region Reports

#pragma endregion

//===================================================
//  Ocugine Unteal Engine 4 SDK Users Module
//===================================================
#pragma region Users

void UOcugineBlueprintLibrary::OcugineGetUsersList(const FString & AppID, const FString & AppKey, const int64 Page, const FOnGetUsersListComplete &SuccessCallback, const FOnError &ErrorCallback)
{
	const FString PostContent = FString::Printf(TEXT("app_id=%s&app_key=%s&lang=%s&page=%s"),
		AppID != "" ? *AppID : *GetDefault<UCustomGameSettings>()->AppID,
		AppKey != "" ? *AppKey : *GetDefault<UCustomGameSettings>()->AppKey,
		*UOcugineBlueprintLibrary::GetApplicationLanguageFromConfig(),
		*FString::FromInt(Page)
	);

	TSharedRef<IHttpRequest> HttpRequest = UOcugineBlueprintLibrary::CreateHttpRequest(UOcugineBlueprintLibrary::USERS_OBJECT, "get_users_list", PostContent);
	HttpRequest->OnProcessRequestComplete().BindStatic(&UOcugineBlueprintLibrary::OcugineGetUsersList_HttpRequestComplete, SuccessCallback, ErrorCallback);
	HttpRequest->ProcessRequest();
}
void UOcugineBlueprintLibrary::OcugineGetUsersList_HttpRequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, FOnGetUsersListComplete SuccessCallback, FOnError ErrorCallback)
{
	if (bSucceeded)
	{ // If request succeeded
		FString ResponseStr = HttpResponse->GetContentAsString(); FOcugineUsersListModel ConvertedResponse; // Declare temp objects
		if (FJsonObjectConverter::JsonObjectStringToUStruct<FOcugineUsersListModel>(ResponseStr, &ConvertedResponse, 0, 0)) // If converted
		{
			if (ConvertedResponse.complete) { SuccessCallback.ExecuteIfBound(ConvertedResponse); } // If complete is true execute callback
			else { ErrorCallback.ExecuteIfBound(TEXT("Ocugine Error"), ConvertedResponse.message); } // If not completed
		}
		else { ErrorCallback.ExecuteIfBound(TEXT("Parse error"), DEFAULT_PARSE_ERROR); } // If convert exception
	}
	else { ErrorCallback.ExecuteIfBound(TEXT("Request error"), DEFAULT_REQUEST_ERROR); } // If request exception
};

void UOcugineBlueprintLibrary::OcugineFindUser(const FString & AppID, const FString & AppKey, const FString & Search, const int64 Page, const FOnFindUserComplete &SuccessCallback, const FOnError &ErrorCallback)
{
	const FString PostContent = FString::Printf(TEXT("app_id=%s&app_key=%s&lang=%s&search=%s&page=%s"),
		AppID != "" ? *AppID : *GetDefault<UCustomGameSettings>()->AppID,
		AppKey != "" ? *AppKey : *GetDefault<UCustomGameSettings>()->AppKey,
		*UOcugineBlueprintLibrary::GetApplicationLanguageFromConfig(),
		*Search,
		*FString::FromInt(Page)
	);

	TSharedRef<IHttpRequest> HttpRequest = UOcugineBlueprintLibrary::CreateHttpRequest(UOcugineBlueprintLibrary::USERS_OBJECT, "find_user", PostContent);
	HttpRequest->OnProcessRequestComplete().BindStatic(&UOcugineBlueprintLibrary::OcugineFindUser_HttpRequestComplete, SuccessCallback, ErrorCallback);
	HttpRequest->ProcessRequest();
}
void UOcugineBlueprintLibrary::OcugineFindUser_HttpRequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, FOnFindUserComplete SuccessCallback, FOnError ErrorCallback)
{
	if (bSucceeded)
	{ // If request succeeded
		FString ResponseStr = HttpResponse->GetContentAsString(); FOcugineUsersListModel ConvertedResponse; // Declare temp objects
		if (FJsonObjectConverter::JsonObjectStringToUStruct<FOcugineUsersListModel>(ResponseStr, &ConvertedResponse, 0, 0)) // If converted
		{
			if (ConvertedResponse.complete) { SuccessCallback.ExecuteIfBound(ConvertedResponse); } // If complete is true execute callback
			else { ErrorCallback.ExecuteIfBound(TEXT("Ocugine Error"), ConvertedResponse.message); } // If not completed
		}
		else { ErrorCallback.ExecuteIfBound(TEXT("Parse error"), DEFAULT_PARSE_ERROR); } // If convert exception
	}
	else { ErrorCallback.ExecuteIfBound(TEXT("Request error"), DEFAULT_REQUEST_ERROR); } // If request exception
};

void UOcugineBlueprintLibrary::OcugineGetUserData(const FString & AppID, const FString & AppKey, const FString & AccessToken, const FOnGetUserDataComplete &SuccessCallback, const FOnError &ErrorCallback)
{
	const FString PostContent = FString::Printf(TEXT("app_id=%s&app_key=%s&lang=%s&access_token=%s"),
		AppID != "" ? *AppID : *GetDefault<UCustomGameSettings>()->AppID,
		AppKey != "" ? *AppKey : *GetDefault<UCustomGameSettings>()->AppKey,
		*UOcugineBlueprintLibrary::GetApplicationLanguageFromConfig(),
		AccessToken != "" ? *AccessToken : *UOcugineBlueprintLibrary::GetDataFromFile("access_token.o", true)
	);

	TSharedRef<IHttpRequest> HttpRequest = UOcugineBlueprintLibrary::CreateHttpRequest(UOcugineBlueprintLibrary::USERS_OBJECT, "get_user_data", PostContent);
	HttpRequest->OnProcessRequestComplete().BindStatic(&UOcugineBlueprintLibrary::OcugineGetUserData_HttpRequestComplete, SuccessCallback, ErrorCallback);
	HttpRequest->ProcessRequest();
}
void UOcugineBlueprintLibrary::OcugineGetUserData_HttpRequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, FOnGetUserDataComplete SuccessCallback, FOnError ErrorCallback)
{
	if (bSucceeded)
	{ // If request succeeded
		FString ResponseStr = HttpResponse->GetContentAsString(); FOcugineUserModel ConvertedResponse; // Declare temp objects
		if (FJsonObjectConverter::JsonObjectStringToUStruct<FOcugineUserModel>(ResponseStr, &ConvertedResponse, 0, 0)) // If converted
		{
			if (ConvertedResponse.complete) { SuccessCallback.ExecuteIfBound(ConvertedResponse); } // If complete is true execute callback
			else { ErrorCallback.ExecuteIfBound(TEXT("Ocugine Error"), ConvertedResponse.message); } // If not completed
		}
		else { ErrorCallback.ExecuteIfBound(TEXT("Parse error"), DEFAULT_PARSE_ERROR); } // If convert exception
	}
	else { ErrorCallback.ExecuteIfBound(TEXT("Request error"), DEFAULT_REQUEST_ERROR); } // If request exception
};

void UOcugineBlueprintLibrary::OcugineGetUserByID(const FString & AppID, const FString & AppKey, const int64 ProfileUid, const FOnGetUserByIDComplete &SuccessCallback, const FOnError &ErrorCallback)
{
	const FString PostContent = FString::Printf(TEXT("app_id=%s&app_key=%s&lang=%s&profile_uid=%s"),
		AppID != "" ? *AppID : *GetDefault<UCustomGameSettings>()->AppID,
		AppKey != "" ? *AppKey : *GetDefault<UCustomGameSettings>()->AppKey,
		*UOcugineBlueprintLibrary::GetApplicationLanguageFromConfig(),
		*FString::FromInt(ProfileUid)
	);

	TSharedRef<IHttpRequest> HttpRequest = UOcugineBlueprintLibrary::CreateHttpRequest(UOcugineBlueprintLibrary::USERS_OBJECT, "get_user_by_id", PostContent);
	HttpRequest->OnProcessRequestComplete().BindStatic(&UOcugineBlueprintLibrary::OcugineGetUserByID_HttpRequestComplete, SuccessCallback, ErrorCallback);
	HttpRequest->ProcessRequest();
}
void UOcugineBlueprintLibrary::OcugineGetUserByID_HttpRequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, FOnGetUserByIDComplete SuccessCallback, FOnError ErrorCallback)
{
	if (bSucceeded)
	{ // If request succeeded
		FString ResponseStr = HttpResponse->GetContentAsString(); FOcugineUserModel ConvertedResponse; // Declare temp objects
		if (FJsonObjectConverter::JsonObjectStringToUStruct<FOcugineUserModel>(ResponseStr, &ConvertedResponse, 0, 0)) // If converted
		{
			if (ConvertedResponse.complete) { SuccessCallback.ExecuteIfBound(ConvertedResponse); } // If complete is true execute callback
			else { ErrorCallback.ExecuteIfBound(TEXT("Ocugine Error"), ConvertedResponse.message); } // If not completed
		}
		else { ErrorCallback.ExecuteIfBound(TEXT("Parse error"), DEFAULT_PARSE_ERROR); } // If convert exception
	}
	else { ErrorCallback.ExecuteIfBound(TEXT("Request error"), DEFAULT_REQUEST_ERROR); } // If request exception
};

void UOcugineBlueprintLibrary::OcugineGetBanState(const FString & AppID, const FString & AppKey, const int64 ProfileUid, const FOnGetBanStateComplete &SuccessCallback, const FOnError &ErrorCallback)
{
	const FString PostContent = FString::Printf(TEXT("app_id=%s&app_key=%s&lang=%s&profile_uid=%s"),
		AppID != "" ? *AppID : *GetDefault<UCustomGameSettings>()->AppID,
		AppKey != "" ? *AppKey : *GetDefault<UCustomGameSettings>()->AppKey,
		*UOcugineBlueprintLibrary::GetApplicationLanguageFromConfig(),
		*FString::FromInt(ProfileUid)
	);

	TSharedRef<IHttpRequest> HttpRequest = UOcugineBlueprintLibrary::CreateHttpRequest(UOcugineBlueprintLibrary::USERS_OBJECT, "get_ban_state", PostContent);
	HttpRequest->OnProcessRequestComplete().BindStatic(&UOcugineBlueprintLibrary::OcugineGetBanState_HttpRequestComplete, SuccessCallback, ErrorCallback);
	HttpRequest->ProcessRequest();
}
void UOcugineBlueprintLibrary::OcugineGetBanState_HttpRequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, FOnGetBanStateComplete SuccessCallback, FOnError ErrorCallback)
{
	if (bSucceeded)
	{ // If request succeeded
		FString ResponseStr = HttpResponse->GetContentAsString(); FOcugineBanStateModel ConvertedResponse; // Declare temp objects
		if (FJsonObjectConverter::JsonObjectStringToUStruct<FOcugineBanStateModel>(ResponseStr, &ConvertedResponse, 0, 0)) // If converted
		{
			if (ConvertedResponse.complete) { SuccessCallback.ExecuteIfBound(ConvertedResponse); } // If complete is true execute callback
			else { ErrorCallback.ExecuteIfBound(TEXT("Ocugine Error"), ConvertedResponse.message); } // If not completed
		}
		else { ErrorCallback.ExecuteIfBound(TEXT("Parse error"), DEFAULT_PARSE_ERROR); } // If convert exception
	}
	else { ErrorCallback.ExecuteIfBound(TEXT("Request error"), DEFAULT_REQUEST_ERROR); } // If request exception
};

void UOcugineBlueprintLibrary::OcugineGetGroupData(const FString & AppID, const FString & AppKey, const int64 GroupId, const FOnGetGroupDataComplete &SuccessCallback, const FOnError &ErrorCallback)
{
	const FString PostContent = FString::Printf(TEXT("app_id=%s&app_key=%s&group_id=%s&lang=%s"),
		AppID != "" ? *AppID : *GetDefault<UCustomGameSettings>()->AppID,
		AppKey != "" ? *AppKey : *GetDefault<UCustomGameSettings>()->AppKey,
		*FString::FromInt(GroupId),
		*UOcugineBlueprintLibrary::GetApplicationLanguageFromConfig()
	);

	TSharedRef<IHttpRequest> HttpRequest = UOcugineBlueprintLibrary::CreateHttpRequest(UOcugineBlueprintLibrary::USERS_OBJECT, "get_group_data", PostContent);
	HttpRequest->OnProcessRequestComplete().BindStatic(&UOcugineBlueprintLibrary::OcugineGetGroupData_HttpRequestComplete, SuccessCallback, ErrorCallback);
	HttpRequest->ProcessRequest();
}
void UOcugineBlueprintLibrary::OcugineGetGroupData_HttpRequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, FOnGetGroupDataComplete SuccessCallback, FOnError ErrorCallback)
{
	if (bSucceeded)
	{ // If request succeeded
		FString ResponseStr = HttpResponse->GetContentAsString(); FOcugineGroupModel ConvertedResponse; // Declare temp objects
		if (FJsonObjectConverter::JsonObjectStringToUStruct<FOcugineGroupModel>(ResponseStr, &ConvertedResponse, 0, 0)) // If converted
		{
			if (ConvertedResponse.complete) { SuccessCallback.ExecuteIfBound(ConvertedResponse); } // If complete is true execute callback
			else { ErrorCallback.ExecuteIfBound(TEXT("Ocugine Error"), ConvertedResponse.message); } // If not completed
		}
		else { ErrorCallback.ExecuteIfBound(TEXT("Parse error"), DEFAULT_PARSE_ERROR); } // If convert exception
	}
	else { ErrorCallback.ExecuteIfBound(TEXT("Request error"), DEFAULT_REQUEST_ERROR); } // If request exception
};

void UOcugineBlueprintLibrary::OcugineGetGroupsList(const FString & AppID, const FString & AppKey, const FOnGetGroupsListComplete &SuccessCallback, const FOnError &ErrorCallback)
{
	const FString PostContent = FString::Printf(TEXT("app_id=%s&app_key=%s&lang=%s"),
		AppID != "" ? *AppID : *GetDefault<UCustomGameSettings>()->AppID,
		AppKey != "" ? *AppKey : *GetDefault<UCustomGameSettings>()->AppKey,
		*UOcugineBlueprintLibrary::GetApplicationLanguageFromConfig()
	);

	TSharedRef<IHttpRequest> HttpRequest = UOcugineBlueprintLibrary::CreateHttpRequest(UOcugineBlueprintLibrary::USERS_OBJECT, "get_group_list", PostContent);
	HttpRequest->OnProcessRequestComplete().BindStatic(&UOcugineBlueprintLibrary::OcugineGetGroupsList_HttpRequestComplete, SuccessCallback, ErrorCallback);
	HttpRequest->ProcessRequest();
}
void UOcugineBlueprintLibrary::OcugineGetGroupsList_HttpRequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, FOnGetGroupsListComplete SuccessCallback, FOnError ErrorCallback)
{
	if (bSucceeded)
	{ // If request succeeded
		FString ResponseStr = HttpResponse->GetContentAsString(); FOcugineGroupsListModel ConvertedResponse; // Declare temp objects
		if (FJsonObjectConverter::JsonObjectStringToUStruct<FOcugineGroupsListModel>(ResponseStr, &ConvertedResponse, 0, 0)) // If converted
		{
			if (ConvertedResponse.complete) { SuccessCallback.ExecuteIfBound(ConvertedResponse); } // If complete is true execute callback
			else { ErrorCallback.ExecuteIfBound(TEXT("Ocugine Error"), ConvertedResponse.message); } // If not completed
		}
		else { ErrorCallback.ExecuteIfBound(TEXT("Parse error"), DEFAULT_PARSE_ERROR); } // If convert exception
	}
	else { ErrorCallback.ExecuteIfBound(TEXT("Request error"), DEFAULT_REQUEST_ERROR); } // If request exception
};

void UOcugineBlueprintLibrary::OcugineSetGroup(const FString & AppID, const FString & AppKey, const FString & AccessToken, const int64 ProfileUid, const int64 GroupId, const FOnSetGroupComplete &SuccessCallback, const FOnError &ErrorCallback)
{
	const FString PostContent = FString::Printf(TEXT("app_id=%s&app_key=%s&lang=%s&access_token=%s&profile_uid=%s&group_id=%s"),
		AppID != "" ? *AppID : *GetDefault<UCustomGameSettings>()->AppID,
		AppKey != "" ? *AppKey : *GetDefault<UCustomGameSettings>()->AppKey,
		*UOcugineBlueprintLibrary::GetApplicationLanguageFromConfig(),
		AccessToken != "" ? *AccessToken : *UOcugineBlueprintLibrary::GetDataFromFile("access_token.o", true),
		*FString::FromInt(ProfileUid),
		*FString::FromInt(GroupId)
	);

	TSharedRef<IHttpRequest> HttpRequest = UOcugineBlueprintLibrary::CreateHttpRequest(UOcugineBlueprintLibrary::USERS_OBJECT, "set_group", PostContent);
	HttpRequest->OnProcessRequestComplete().BindStatic(&UOcugineBlueprintLibrary::OcugineSetGroup_HttpRequestComplete, SuccessCallback, ErrorCallback);
	HttpRequest->ProcessRequest();
}
void UOcugineBlueprintLibrary::OcugineSetGroup_HttpRequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, FOnSetGroupComplete SuccessCallback, FOnError ErrorCallback)
{
	if (bSucceeded)
	{ // If request succeeded
		FString ResponseStr = HttpResponse->GetContentAsString(); FOcugineBaseModel ConvertedResponse; // Declare temp objects
		if (FJsonObjectConverter::JsonObjectStringToUStruct<FOcugineBaseModel>(ResponseStr, &ConvertedResponse, 0, 0)) // If converted
		{
			if (ConvertedResponse.complete) { SuccessCallback.ExecuteIfBound(ConvertedResponse); } // If complete is true execute callback
			else { ErrorCallback.ExecuteIfBound(TEXT("Ocugine Error"), ConvertedResponse.message); } // If not completed
		}
		else { ErrorCallback.ExecuteIfBound(TEXT("Parse error"), DEFAULT_PARSE_ERROR); } // If convert exception
	}
	else { ErrorCallback.ExecuteIfBound(TEXT("Request error"), DEFAULT_REQUEST_ERROR); } // If request exception
};

void UOcugineBlueprintLibrary::OcugineGetAdvancedFields(const FString & AppID, const FString & AppKey, const int64 Page, const FString & Search, const FOnGetAdvancedFieldsComplete &SuccessCallback, const FOnError &ErrorCallback)
{
	const FString PostContent = FString::Printf(TEXT("app_id=%s&app_key=%s&page=%s&search=%s"),
		AppID != "" ? *AppID : *GetDefault<UCustomGameSettings>()->AppID,
		AppKey != "" ? *AppKey : *GetDefault<UCustomGameSettings>()->AppKey,
		*FString::FromInt(Page),
		*Search
	);

	TSharedRef<IHttpRequest> HttpRequest = UOcugineBlueprintLibrary::CreateHttpRequest(UOcugineBlueprintLibrary::USERS_OBJECT, "get_fields", PostContent);
	HttpRequest->OnProcessRequestComplete().BindStatic(&UOcugineBlueprintLibrary::OcugineGetAdvancedFields_HttpRequestComplete, SuccessCallback, ErrorCallback);
	HttpRequest->ProcessRequest();
}
void UOcugineBlueprintLibrary::OcugineGetAdvancedFields_HttpRequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, FOnGetAdvancedFieldsComplete SuccessCallback, FOnError ErrorCallback)
{
	if (bSucceeded)
	{ // If request succeeded
		FString ResponseStr = HttpResponse->GetContentAsString(); FOcugineAdvancedFieldsListModel ConvertedResponse; // Declare temp objects
		if (FJsonObjectConverter::JsonObjectStringToUStruct<FOcugineAdvancedFieldsListModel>(ResponseStr, &ConvertedResponse, 0, 0)) // If converted
		{
			if (ConvertedResponse.complete) { SuccessCallback.ExecuteIfBound(ConvertedResponse); } // If complete is true execute callback
			else { ErrorCallback.ExecuteIfBound(TEXT("Ocugine Error"), ConvertedResponse.message); } // If not completed
		}
		else { ErrorCallback.ExecuteIfBound(TEXT("Parse error"), DEFAULT_PARSE_ERROR); } // If convert exception
	}
	else { ErrorCallback.ExecuteIfBound(TEXT("Request error"), DEFAULT_REQUEST_ERROR); } // If request exception
};

void UOcugineBlueprintLibrary::OcugineSetAdvancedField(const FString & AppID, const FString & AppKey, const FString & AccessToken, const int64 ProfileUid, const int64 FieldId, const FString & Value, const FOnSetAdvancedFieldComplete &SuccessCallback, const FOnError &ErrorCallback)
{
	const FString PostContent = FString::Printf(TEXT("app_id=%s&app_key=%s&lang=%s&access_token=%s&profile_uid=%s&field_id=%s&value=%s"),
		AppID != "" ? *AppID : *GetDefault<UCustomGameSettings>()->AppID,
		AppKey != "" ? *AppKey : *GetDefault<UCustomGameSettings>()->AppKey,
		*UOcugineBlueprintLibrary::GetApplicationLanguageFromConfig(),
		AccessToken != "" ? *AccessToken : *UOcugineBlueprintLibrary::GetDataFromFile("access_token.o", true),
		*FString::FromInt(ProfileUid),
		*FString::FromInt(FieldId),
		*Value
	);

	TSharedRef<IHttpRequest> HttpRequest = UOcugineBlueprintLibrary::CreateHttpRequest(UOcugineBlueprintLibrary::USERS_OBJECT, "set_field", PostContent);
	HttpRequest->OnProcessRequestComplete().BindStatic(&UOcugineBlueprintLibrary::OcugineSetAdvancedField_HttpRequestComplete, SuccessCallback, ErrorCallback);
	HttpRequest->ProcessRequest();
}
void UOcugineBlueprintLibrary::OcugineSetAdvancedField_HttpRequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, FOnSetAdvancedFieldComplete SuccessCallback, FOnError ErrorCallback)
{
	if (bSucceeded)
	{ // If request succeeded
		FString ResponseStr = HttpResponse->GetContentAsString(); FOcugineBaseModel ConvertedResponse; // Declare temp objects
		if (FJsonObjectConverter::JsonObjectStringToUStruct<FOcugineBaseModel>(ResponseStr, &ConvertedResponse, 0, 0)) // If converted
		{
			if (ConvertedResponse.complete) { SuccessCallback.ExecuteIfBound(ConvertedResponse); } // If complete is true execute callback
			else { ErrorCallback.ExecuteIfBound(TEXT("Ocugine Error"), ConvertedResponse.message); } // If not completed
		}
		else { ErrorCallback.ExecuteIfBound(TEXT("Parse error"), DEFAULT_PARSE_ERROR); } // If convert exception
	}
	else { ErrorCallback.ExecuteIfBound(TEXT("Request error"), DEFAULT_REQUEST_ERROR); } // If request exception
};

void UOcugineBlueprintLibrary::OcugineGetSupportCategories(const FString & AppID, const FString & AppKey, const FOnGetSupportCategoriesComplete &SuccessCallback, const FOnError &ErrorCallback)
{
	const FString PostContent = FString::Printf(TEXT("app_id=%s&app_key=%s&lang=%s"),
		AppID != "" ? *AppID : *GetDefault<UCustomGameSettings>()->AppID,
		AppKey != "" ? *AppKey : *GetDefault<UCustomGameSettings>()->AppKey,
		*UOcugineBlueprintLibrary::GetApplicationLanguageFromConfig()
	);

	TSharedRef<IHttpRequest> HttpRequest = UOcugineBlueprintLibrary::CreateHttpRequest(UOcugineBlueprintLibrary::USERS_OBJECT, "get_support_categories", PostContent);
	HttpRequest->OnProcessRequestComplete().BindStatic(&UOcugineBlueprintLibrary::OcugineGetSupportCategories_HttpRequestComplete, SuccessCallback, ErrorCallback);
	HttpRequest->ProcessRequest();
}
void UOcugineBlueprintLibrary::OcugineGetSupportCategories_HttpRequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, FOnGetSupportCategoriesComplete SuccessCallback, FOnError ErrorCallback)
{
	if (bSucceeded)
	{ // If request succeeded
		FString ResponseStr = HttpResponse->GetContentAsString(); FOcugineSupportCategoriesListModel ConvertedResponse; // Declare temp objects
		if (FJsonObjectConverter::JsonObjectStringToUStruct<FOcugineSupportCategoriesListModel>(ResponseStr, &ConvertedResponse, 0, 0)) // If converted
		{
			if (ConvertedResponse.complete) { SuccessCallback.ExecuteIfBound(ConvertedResponse); } // If complete is true execute callback
			else { ErrorCallback.ExecuteIfBound(TEXT("Ocugine Error"), ConvertedResponse.message); } // If not completed
		}
		else { ErrorCallback.ExecuteIfBound(TEXT("Parse error"), DEFAULT_PARSE_ERROR); } // If convert exception
	}
	else { ErrorCallback.ExecuteIfBound(TEXT("Request error"), DEFAULT_REQUEST_ERROR); } // If request exception
};

void UOcugineBlueprintLibrary::OcugineGetSupportTopics(const FString & AppID, const FString & AppKey, const int64 CategoryUid, const int64 Page, const FString & Search, const FOnGetSupportTopicsComplete &SuccessCallback, const FOnError &ErrorCallback)
{
	const FString PostContent = FString::Printf(TEXT("app_id=%s&app_key=%s&category_uid=%s&page=%s&search=%s"),
		AppID != "" ? *AppID : *GetDefault<UCustomGameSettings>()->AppID,
		AppKey != "" ? *AppKey : *GetDefault<UCustomGameSettings>()->AppKey,
		*FString::FromInt(CategoryUid),
		*FString::FromInt(Page),
		*Search
	);

	TSharedRef<IHttpRequest> HttpRequest = UOcugineBlueprintLibrary::CreateHttpRequest(UOcugineBlueprintLibrary::USERS_OBJECT, "get_support_topics", PostContent);
	HttpRequest->OnProcessRequestComplete().BindStatic(&UOcugineBlueprintLibrary::OcugineGetSupportTopics_HttpRequestComplete, SuccessCallback, ErrorCallback);
	HttpRequest->ProcessRequest();
}
void UOcugineBlueprintLibrary::OcugineGetSupportTopics_HttpRequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, FOnGetSupportTopicsComplete SuccessCallback, FOnError ErrorCallback)
{
	if (bSucceeded)
	{ // If request succeeded
		FString ResponseStr = HttpResponse->GetContentAsString(); FOcugineSupportTopicsListModel ConvertedResponse; // Declare temp objects
		if (FJsonObjectConverter::JsonObjectStringToUStruct<FOcugineSupportTopicsListModel>(ResponseStr, &ConvertedResponse, 0, 0)) // If converted
		{
			if (ConvertedResponse.complete) { SuccessCallback.ExecuteIfBound(ConvertedResponse); } // If complete is true execute callback
			else { ErrorCallback.ExecuteIfBound(TEXT("Ocugine Error"), ConvertedResponse.message); } // If not completed
		}
		else { ErrorCallback.ExecuteIfBound(TEXT("Parse error"), DEFAULT_PARSE_ERROR); } // If convert exception
	}
	else { ErrorCallback.ExecuteIfBound(TEXT("Request error"), DEFAULT_REQUEST_ERROR); } // If request exception
};

void UOcugineBlueprintLibrary::OcugineGetSupportMessages(const FString & AppID, const FString & AppKey, const int64 TopicUid, const int64 Page, const FString & Search, const FOnGetSupportMessagesComplete &SuccessCallback, const FOnError &ErrorCallback)
{
	const FString PostContent = FString::Printf(TEXT("app_id=%s&app_key=%s&topic_uid=%s&page=%s&search=%s"),
		AppID != "" ? *AppID : *GetDefault<UCustomGameSettings>()->AppID,
		AppKey != "" ? *AppKey : *GetDefault<UCustomGameSettings>()->AppKey,
		*FString::FromInt(TopicUid),
		*FString::FromInt(Page),
		*Search
	);

	TSharedRef<IHttpRequest> HttpRequest = UOcugineBlueprintLibrary::CreateHttpRequest(UOcugineBlueprintLibrary::USERS_OBJECT, "get_support_messages", PostContent);
	HttpRequest->OnProcessRequestComplete().BindStatic(&UOcugineBlueprintLibrary::OcugineGetSupportMessages_HttpRequestComplete, SuccessCallback, ErrorCallback);
	HttpRequest->ProcessRequest();
}
void UOcugineBlueprintLibrary::OcugineGetSupportMessages_HttpRequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, FOnGetSupportMessagesComplete SuccessCallback, FOnError ErrorCallback)
{
	if (bSucceeded)
	{ // If request succeeded
		FString ResponseStr = HttpResponse->GetContentAsString(); FOcugineSupportMessagesListModel ConvertedResponse; // Declare temp objects
		if (FJsonObjectConverter::JsonObjectStringToUStruct<FOcugineSupportMessagesListModel>(ResponseStr, &ConvertedResponse, 0, 0)) // If converted
		{
			if (ConvertedResponse.complete) { SuccessCallback.ExecuteIfBound(ConvertedResponse); } // If complete is true execute callback
			else { ErrorCallback.ExecuteIfBound(TEXT("Ocugine Error"), ConvertedResponse.message); } // If not completed
		}
		else { ErrorCallback.ExecuteIfBound(TEXT("Parse error"), DEFAULT_PARSE_ERROR); } // If convert exception
	}
	else { ErrorCallback.ExecuteIfBound(TEXT("Request error"), DEFAULT_REQUEST_ERROR); } // If request exception
};

void UOcugineBlueprintLibrary::OcugineCreateSupportTopic(const FString & AppID, const FString & AppKey, const FString & AccessToken, const int64 CategoryUid, const FString & Name, const FString & Body, const FOnCreateSupportTopicComplete &SuccessCallback, const FOnError &ErrorCallback)
{
	const FString PostContent = FString::Printf(TEXT("app_id=%s&app_key=%s&lang=%s&access_token=%s&category_uid=%s&name=%s&body=%s"),
		AppID != "" ? *AppID : *GetDefault<UCustomGameSettings>()->AppID,
		AppKey != "" ? *AppKey : *GetDefault<UCustomGameSettings>()->AppKey,
		*UOcugineBlueprintLibrary::GetApplicationLanguageFromConfig(),
		AccessToken != "" ? *AccessToken : *UOcugineBlueprintLibrary::GetDataFromFile("access_token.o", true),
		*FString::FromInt(CategoryUid),
		*Name,
		*Body
	);

	TSharedRef<IHttpRequest> HttpRequest = UOcugineBlueprintLibrary::CreateHttpRequest(UOcugineBlueprintLibrary::USERS_OBJECT, "create_topic", PostContent);
	HttpRequest->OnProcessRequestComplete().BindStatic(&UOcugineBlueprintLibrary::OcugineCreateSupportTopic_HttpRequestComplete, SuccessCallback, ErrorCallback);
	HttpRequest->ProcessRequest();
}
void UOcugineBlueprintLibrary::OcugineCreateSupportTopic_HttpRequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, FOnCreateSupportTopicComplete SuccessCallback, FOnError ErrorCallback)
{
	if (bSucceeded)
	{ // If request succeeded
		FString ResponseStr = HttpResponse->GetContentAsString(); FOcugineBaseModel ConvertedResponse; // Declare temp objects
		if (FJsonObjectConverter::JsonObjectStringToUStruct<FOcugineBaseModel>(ResponseStr, &ConvertedResponse, 0, 0)) // If converted
		{
			if (ConvertedResponse.complete) { SuccessCallback.ExecuteIfBound(ConvertedResponse); } // If complete is true execute callback
			else { ErrorCallback.ExecuteIfBound(TEXT("Ocugine Error"), ConvertedResponse.message); } // If not completed
		}
		else { ErrorCallback.ExecuteIfBound(TEXT("Parse error"), DEFAULT_PARSE_ERROR); } // If convert exception
	}
	else { ErrorCallback.ExecuteIfBound(TEXT("Request error"), DEFAULT_REQUEST_ERROR); } // If request exception
};

void UOcugineBlueprintLibrary::OcugineUpdateSupportTopic(const FString & AppID, const FString & AppKey, const FString & AccessToken, const int64 CategoryUid, const int64 TopicUid, const FString & Name, const FString & Body, const FOnUpdateSupportTopicComplete &SuccessCallback, const FOnError &ErrorCallback)
{
	const FString PostContent = FString::Printf(TEXT("app_id=%s&app_key=%s&lang=%s&access_token=%s&category_uid=%s&topic_uid=%s&name=%s&body=%s"),
		AppID != "" ? *AppID : *GetDefault<UCustomGameSettings>()->AppID,
		AppKey != "" ? *AppKey : *GetDefault<UCustomGameSettings>()->AppKey,
		*UOcugineBlueprintLibrary::GetApplicationLanguageFromConfig(),
		AccessToken != "" ? *AccessToken : *UOcugineBlueprintLibrary::GetDataFromFile("access_token.o", true),
		*FString::FromInt(CategoryUid),
		*FString::FromInt(TopicUid),
		*Name,
		*Body
	);

	TSharedRef<IHttpRequest> HttpRequest = UOcugineBlueprintLibrary::CreateHttpRequest(UOcugineBlueprintLibrary::USERS_OBJECT, "update_topic", PostContent);
	HttpRequest->OnProcessRequestComplete().BindStatic(&UOcugineBlueprintLibrary::OcugineUpdateSupportTopic_HttpRequestComplete, SuccessCallback, ErrorCallback);
	HttpRequest->ProcessRequest();
}
void UOcugineBlueprintLibrary::OcugineUpdateSupportTopic_HttpRequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, FOnUpdateSupportTopicComplete SuccessCallback, FOnError ErrorCallback)
{
	if (bSucceeded)
	{ // If request succeeded
		FString ResponseStr = HttpResponse->GetContentAsString(); FOcugineBaseModel ConvertedResponse; // Declare temp objects
		if (FJsonObjectConverter::JsonObjectStringToUStruct<FOcugineBaseModel>(ResponseStr, &ConvertedResponse, 0, 0)) // If converted
		{
			if (ConvertedResponse.complete) { SuccessCallback.ExecuteIfBound(ConvertedResponse); } // If complete is true execute callback
			else { ErrorCallback.ExecuteIfBound(TEXT("Ocugine Error"), ConvertedResponse.message); } // If not completed
		}
		else { ErrorCallback.ExecuteIfBound(TEXT("Parse error"), DEFAULT_PARSE_ERROR); } // If convert exception
	}
	else { ErrorCallback.ExecuteIfBound(TEXT("Request error"), DEFAULT_REQUEST_ERROR); } // If request exception
};

void UOcugineBlueprintLibrary::OcugineCloseSupportTopic(const FString & AppID, const FString & AppKey, const FString & AccessToken, const int64 TopicUid, const FOnCloseSupportTopicComplete &SuccessCallback, const FOnError &ErrorCallback)
{
	const FString PostContent = FString::Printf(TEXT("app_id=%s&app_key=%s&lang=%s&access_token=%s&topic_uid=%s"),
		AppID != "" ? *AppID : *GetDefault<UCustomGameSettings>()->AppID,
		AppKey != "" ? *AppKey : *GetDefault<UCustomGameSettings>()->AppKey,
		*UOcugineBlueprintLibrary::GetApplicationLanguageFromConfig(),
		AccessToken != "" ? *AccessToken : *UOcugineBlueprintLibrary::GetDataFromFile("access_token.o", true),
		*FString::FromInt(TopicUid)
	);

	TSharedRef<IHttpRequest> HttpRequest = UOcugineBlueprintLibrary::CreateHttpRequest(UOcugineBlueprintLibrary::USERS_OBJECT, "close_topic", PostContent);
	HttpRequest->OnProcessRequestComplete().BindStatic(&UOcugineBlueprintLibrary::OcugineCloseSupportTopic_HttpRequestComplete, SuccessCallback, ErrorCallback);
	HttpRequest->ProcessRequest();
}
void UOcugineBlueprintLibrary::OcugineCloseSupportTopic_HttpRequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, FOnCloseSupportTopicComplete SuccessCallback, FOnError ErrorCallback)
{
	if (bSucceeded)
	{ // If request succeeded
		FString ResponseStr = HttpResponse->GetContentAsString(); FOcugineBaseModel ConvertedResponse; // Declare temp objects
		if (FJsonObjectConverter::JsonObjectStringToUStruct<FOcugineBaseModel>(ResponseStr, &ConvertedResponse, 0, 0)) // If converted
		{
			if (ConvertedResponse.complete) { SuccessCallback.ExecuteIfBound(ConvertedResponse); } // If complete is true execute callback
			else { ErrorCallback.ExecuteIfBound(TEXT("Ocugine Error"), ConvertedResponse.message); } // If not completed
		}
		else { ErrorCallback.ExecuteIfBound(TEXT("Parse error"), DEFAULT_PARSE_ERROR); } // If convert exception
	}
	else { ErrorCallback.ExecuteIfBound(TEXT("Request error"), DEFAULT_REQUEST_ERROR); } // If request exception
};

void UOcugineBlueprintLibrary::OcugineSendSupportMessage(const FString & AppID, const FString & AppKey, const FString & AccessToken, const int64 TopicUid, const FString & Message, const FOnSendSupportMessageComplete &SuccessCallback, const FOnError &ErrorCallback)
{
	const FString PostContent = FString::Printf(TEXT("app_id=%s&app_key=%s&lang=%s&access_token=%s&topic_uid=%s&message=%s"),
		AppID != "" ? *AppID : *GetDefault<UCustomGameSettings>()->AppID,
		AppKey != "" ? *AppKey : *GetDefault<UCustomGameSettings>()->AppKey,
		*UOcugineBlueprintLibrary::GetApplicationLanguageFromConfig(),
		AccessToken != "" ? *AccessToken : *UOcugineBlueprintLibrary::GetDataFromFile("access_token.o", true),
		*FString::FromInt(TopicUid),
		*Message
	);

	TSharedRef<IHttpRequest> HttpRequest = UOcugineBlueprintLibrary::CreateHttpRequest(UOcugineBlueprintLibrary::USERS_OBJECT, "send_support_message", PostContent);
	HttpRequest->OnProcessRequestComplete().BindStatic(&UOcugineBlueprintLibrary::OcugineSendSupportMessage_HttpRequestComplete, SuccessCallback, ErrorCallback);
	HttpRequest->ProcessRequest();
}
void UOcugineBlueprintLibrary::OcugineSendSupportMessage_HttpRequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, FOnSendSupportMessageComplete SuccessCallback, FOnError ErrorCallback)
{
	if (bSucceeded)
	{ // If request succeeded
		FString ResponseStr = HttpResponse->GetContentAsString(); FOcugineBaseModel ConvertedResponse; // Declare temp objects
		if (FJsonObjectConverter::JsonObjectStringToUStruct<FOcugineBaseModel>(ResponseStr, &ConvertedResponse, 0, 0)) // If converted
		{
			if (ConvertedResponse.complete) { SuccessCallback.ExecuteIfBound(ConvertedResponse); } // If complete is true execute callback
			else { ErrorCallback.ExecuteIfBound(TEXT("Ocugine Error"), ConvertedResponse.message); } // If not completed
		}
		else { ErrorCallback.ExecuteIfBound(TEXT("Parse error"), DEFAULT_PARSE_ERROR); } // If convert exception
	}
	else { ErrorCallback.ExecuteIfBound(TEXT("Request error"), DEFAULT_REQUEST_ERROR); } // If request exception
};

void UOcugineBlueprintLibrary::OcugineGetChatRooms(const FString & AppID, const FString & AppKey, const FOnGetChatRoomsComplete &SuccessCallback, const FOnError &ErrorCallback)
{
	const FString PostContent = FString::Printf(TEXT("app_id=%s&app_key=%s&lang=%s"),
		AppID != "" ? *AppID : *GetDefault<UCustomGameSettings>()->AppID,
		AppKey != "" ? *AppKey : *GetDefault<UCustomGameSettings>()->AppKey,
		*UOcugineBlueprintLibrary::GetApplicationLanguageFromConfig()
	);

	TSharedRef<IHttpRequest> HttpRequest = UOcugineBlueprintLibrary::CreateHttpRequest(UOcugineBlueprintLibrary::USERS_OBJECT, "get_available_rooms", PostContent);
	HttpRequest->OnProcessRequestComplete().BindStatic(&UOcugineBlueprintLibrary::OcugineGetChatRooms_HttpRequestComplete, SuccessCallback, ErrorCallback);
	HttpRequest->ProcessRequest();
}
void UOcugineBlueprintLibrary::OcugineGetChatRooms_HttpRequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, FOnGetChatRoomsComplete SuccessCallback, FOnError ErrorCallback)
{
	if (bSucceeded)
	{ // If request succeeded
		FString ResponseStr = HttpResponse->GetContentAsString(); FOcugineChatRoomsListModel ConvertedResponse; // Declare temp objects
		if (FJsonObjectConverter::JsonObjectStringToUStruct<FOcugineChatRoomsListModel>(ResponseStr, &ConvertedResponse, 0, 0)) // If converted
		{
			if (ConvertedResponse.complete) { SuccessCallback.ExecuteIfBound(ConvertedResponse); } // If complete is true execute callback
			else { ErrorCallback.ExecuteIfBound(TEXT("Ocugine Error"), ConvertedResponse.message); } // If not completed
		}
		else { ErrorCallback.ExecuteIfBound(TEXT("Parse error"), DEFAULT_PARSE_ERROR); } // If convert exception
	}
	else { ErrorCallback.ExecuteIfBound(TEXT("Request error"), DEFAULT_REQUEST_ERROR); } // If request exception
};

void UOcugineBlueprintLibrary::OcugineGetChatMessages(const FString & AppID, const FString & AppKey, const int64 RoomId, const FOnGetChatMessagesComplete &SuccessCallback, const FOnError &ErrorCallback)
{
	const FString PostContent = FString::Printf(TEXT("app_id=%s&app_key=%s&lang=%s&room_id=%s"),
		AppID != "" ? *AppID : *GetDefault<UCustomGameSettings>()->AppID,
		AppKey != "" ? *AppKey : *GetDefault<UCustomGameSettings>()->AppKey,
		*UOcugineBlueprintLibrary::GetApplicationLanguageFromConfig(),
		*FString::FromInt(RoomId)
	);

	TSharedRef<IHttpRequest> HttpRequest = UOcugineBlueprintLibrary::CreateHttpRequest(UOcugineBlueprintLibrary::USERS_OBJECT, "get_chat_messages", PostContent);
	HttpRequest->OnProcessRequestComplete().BindStatic(&UOcugineBlueprintLibrary::OcugineGetChatMessages_HttpRequestComplete, SuccessCallback, ErrorCallback);
	HttpRequest->ProcessRequest();
}
void UOcugineBlueprintLibrary::OcugineGetChatMessages_HttpRequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, FOnGetChatMessagesComplete SuccessCallback, FOnError ErrorCallback)
{
	if (bSucceeded)
	{ // If request succeeded
		FString ResponseStr = HttpResponse->GetContentAsString(); FOcugineChatMessagesListModel ConvertedResponse; // Declare temp objects
		if (FJsonObjectConverter::JsonObjectStringToUStruct<FOcugineChatMessagesListModel>(ResponseStr, &ConvertedResponse, 0, 0)) // If converted
		{
			if (ConvertedResponse.complete) { SuccessCallback.ExecuteIfBound(ConvertedResponse); } // If complete is true execute callback
			else { ErrorCallback.ExecuteIfBound(TEXT("Ocugine Error"), ConvertedResponse.message); } // If not completed
		}
		else { ErrorCallback.ExecuteIfBound(TEXT("Parse error"), DEFAULT_PARSE_ERROR); } // If convert exception
	}
	else { ErrorCallback.ExecuteIfBound(TEXT("Request error"), DEFAULT_REQUEST_ERROR); } // If request exception
};

void UOcugineBlueprintLibrary::OcugineSendChatMessage(const FString & AppID, const FString & AppKey, const FString & AccessToken, const int64 RoomId, const FString & Message, const FOnSendChatMessageComplete &SuccessCallback, const FOnError &ErrorCallback)
{
	const FString PostContent = FString::Printf(TEXT("app_id=%s&app_key=%s&lang=%s&access_token=%s&room_id=%s&message=%s"),
		AppID != "" ? *AppID : *GetDefault<UCustomGameSettings>()->AppID,
		AppKey != "" ? *AppKey : *GetDefault<UCustomGameSettings>()->AppKey,
		*UOcugineBlueprintLibrary::GetApplicationLanguageFromConfig(),
		AccessToken != "" ? *AccessToken : *UOcugineBlueprintLibrary::GetDataFromFile("access_token.o", true),
		*FString::FromInt(RoomId),
		*Message
	);

	TSharedRef<IHttpRequest> HttpRequest = UOcugineBlueprintLibrary::CreateHttpRequest(UOcugineBlueprintLibrary::USERS_OBJECT, "send_cmessage", PostContent);
	HttpRequest->OnProcessRequestComplete().BindStatic(&UOcugineBlueprintLibrary::OcugineSendChatMessage_HttpRequestComplete, SuccessCallback, ErrorCallback);
	HttpRequest->ProcessRequest();
}
void UOcugineBlueprintLibrary::OcugineSendChatMessage_HttpRequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, FOnSendChatMessageComplete SuccessCallback, FOnError ErrorCallback)
{
	if (bSucceeded)
	{ // If request succeeded
		FString ResponseStr = HttpResponse->GetContentAsString(); FOcugineBaseModel ConvertedResponse; // Declare temp objects
		if (FJsonObjectConverter::JsonObjectStringToUStruct<FOcugineBaseModel>(ResponseStr, &ConvertedResponse, 0, 0)) // If converted
		{
			if (ConvertedResponse.complete) { SuccessCallback.ExecuteIfBound(ConvertedResponse); } // If complete is true execute callback
			else { ErrorCallback.ExecuteIfBound(TEXT("Ocugine Error"), ConvertedResponse.message); } // If not completed
		}
		else { ErrorCallback.ExecuteIfBound(TEXT("Parse error"), DEFAULT_PARSE_ERROR); } // If convert exception
	}
	else { ErrorCallback.ExecuteIfBound(TEXT("Request error"), DEFAULT_REQUEST_ERROR); } // If request exception
};

void UOcugineBlueprintLibrary::OcugineSendReview(const FString & AppID, const FString & AppKey, const FString & AccessToken, const FString & Message, const int64 Stars, const FOnSendReviewComplete &SuccessCallback, const FOnError &ErrorCallback)
{
	const FString PostContent = FString::Printf(TEXT("app_id=%s&app_key=%s&lang=%s&access_token=%s&message=%s&stars=%s"),
		AppID != "" ? *AppID : *GetDefault<UCustomGameSettings>()->AppID,
		AppKey != "" ? *AppKey : *GetDefault<UCustomGameSettings>()->AppKey,
		*UOcugineBlueprintLibrary::GetApplicationLanguageFromConfig(),
		AccessToken != "" ? *AccessToken : *UOcugineBlueprintLibrary::GetDataFromFile("access_token.o", true),
		*Message,
		*FString::FromInt(Stars)
	);

	TSharedRef<IHttpRequest> HttpRequest = UOcugineBlueprintLibrary::CreateHttpRequest(UOcugineBlueprintLibrary::USERS_OBJECT, "send_review", PostContent);
	HttpRequest->OnProcessRequestComplete().BindStatic(&UOcugineBlueprintLibrary::OcugineSendReview_HttpRequestComplete, SuccessCallback, ErrorCallback);
	HttpRequest->ProcessRequest();
}
void UOcugineBlueprintLibrary::OcugineSendReview_HttpRequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, FOnSendReviewComplete SuccessCallback, FOnError ErrorCallback)
{
	if (bSucceeded)
	{ // If request succeeded
		FString ResponseStr = HttpResponse->GetContentAsString(); FOcugineReviewsListModel ConvertedResponse; // Declare temp objects
		if (FJsonObjectConverter::JsonObjectStringToUStruct<FOcugineReviewsListModel>(ResponseStr, &ConvertedResponse, 0, 0)) // If converted
		{
			if (ConvertedResponse.complete) { SuccessCallback.ExecuteIfBound(ConvertedResponse); } // If complete is true execute callback
			else { ErrorCallback.ExecuteIfBound(TEXT("Ocugine Error"), ConvertedResponse.message); } // If not completed
		}
		else { ErrorCallback.ExecuteIfBound(TEXT("Parse error"), DEFAULT_PARSE_ERROR); } // If convert exception
	}
	else { ErrorCallback.ExecuteIfBound(TEXT("Request error"), DEFAULT_REQUEST_ERROR); } // If request exception
};

void UOcugineBlueprintLibrary::OcugineGetReviewsList(const FString & AppID, const FString & AppKey, const int64 Page, const FString & Search, const FOnGetReviewsListComplete &SuccessCallback, const FOnError &ErrorCallback)
{
	const FString PostContent = FString::Printf(TEXT("app_id=%s&app_key=%s&lang=%s&page=%s&search=%s"),
		AppID != "" ? *AppID : *GetDefault<UCustomGameSettings>()->AppID,
		AppKey != "" ? *AppKey : *GetDefault<UCustomGameSettings>()->AppKey,
		*UOcugineBlueprintLibrary::GetApplicationLanguageFromConfig(),
		*FString::FromInt(Page),
		*Search
	);

	TSharedRef<IHttpRequest> HttpRequest = UOcugineBlueprintLibrary::CreateHttpRequest(UOcugineBlueprintLibrary::USERS_OBJECT, "get_reviews", PostContent);
	HttpRequest->OnProcessRequestComplete().BindStatic(&UOcugineBlueprintLibrary::OcugineGetReviewsList_HttpRequestComplete, SuccessCallback, ErrorCallback);
	HttpRequest->ProcessRequest();
}
void UOcugineBlueprintLibrary::OcugineGetReviewsList_HttpRequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, FOnGetReviewsListComplete SuccessCallback, FOnError ErrorCallback)
{
	if (bSucceeded)
	{ // If request succeeded
		FString ResponseStr = HttpResponse->GetContentAsString(); FOcugineReviewsListModel ConvertedResponse; // Declare temp objects
		if (FJsonObjectConverter::JsonObjectStringToUStruct<FOcugineReviewsListModel>(ResponseStr, &ConvertedResponse, 0, 0)) // If converted
		{
			if (ConvertedResponse.complete) { SuccessCallback.ExecuteIfBound(ConvertedResponse); } // If complete is true execute callback
			else { ErrorCallback.ExecuteIfBound(TEXT("Ocugine Error"), ConvertedResponse.message); } // If not completed
		}
		else { ErrorCallback.ExecuteIfBound(TEXT("Parse error"), DEFAULT_PARSE_ERROR); } // If convert exception
	}
	else { ErrorCallback.ExecuteIfBound(TEXT("Request error"), DEFAULT_REQUEST_ERROR); } // If request exception
};

void UOcugineBlueprintLibrary::OcugineGetPolicyList(const FString & AppID, const FString & AppKey, const FOnGetPolicyListComplete &SuccessCallback, const FOnError &ErrorCallback)
{
	const FString PostContent = FString::Printf(TEXT("app_id=%s&app_key=%s&lang=%s"),
		AppID != "" ? *AppID : *GetDefault<UCustomGameSettings>()->AppID,
		AppKey != "" ? *AppKey : *GetDefault<UCustomGameSettings>()->AppKey,
		*UOcugineBlueprintLibrary::GetApplicationLanguageFromConfig()
	);

	TSharedRef<IHttpRequest> HttpRequest = UOcugineBlueprintLibrary::CreateHttpRequest(UOcugineBlueprintLibrary::USERS_OBJECT, "get_policy_list", PostContent);
	HttpRequest->OnProcessRequestComplete().BindStatic(&UOcugineBlueprintLibrary::OcugineGetPolicyList_HttpRequestComplete, SuccessCallback, ErrorCallback);
	HttpRequest->ProcessRequest();
}
void UOcugineBlueprintLibrary::OcugineGetPolicyList_HttpRequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, FOnGetPolicyListComplete SuccessCallback, FOnError ErrorCallback)
{
	if (bSucceeded)
	{ // If request succeeded
		FString ResponseStr = HttpResponse->GetContentAsString(); FOcuginePolicyListModel ConvertedResponse; // Declare temp objects
		if (FJsonObjectConverter::JsonObjectStringToUStruct<FOcuginePolicyListModel>(ResponseStr, &ConvertedResponse, 0, 0)) // If converted
		{
			if (ConvertedResponse.complete) { SuccessCallback.ExecuteIfBound(ConvertedResponse); } // If complete is true execute callback
			else { ErrorCallback.ExecuteIfBound(TEXT("Ocugine Error"), ConvertedResponse.message); } // If not completed
		}
		else { ErrorCallback.ExecuteIfBound(TEXT("Parse error"), DEFAULT_PARSE_ERROR); } // If convert exception
	}
	else { ErrorCallback.ExecuteIfBound(TEXT("Request error"), DEFAULT_REQUEST_ERROR); } // If request exception
};

void UOcugineBlueprintLibrary::OcugineGetPolicyInfo(const FString & AppID, const FString & AppKey, const int64 Pid, const FOnGetPolicyInfoComplete &SuccessCallback, const FOnError &ErrorCallback)
{
	const FString PostContent = FString::Printf(TEXT("app_id=%s&app_key=%s&lang=%s&pid=%s"),
		AppID != "" ? *AppID : *GetDefault<UCustomGameSettings>()->AppID,
		AppKey != "" ? *AppKey : *GetDefault<UCustomGameSettings>()->AppKey,
		*UOcugineBlueprintLibrary::GetApplicationLanguageFromConfig(),
		*FString::FromInt(Pid)
	);

	TSharedRef<IHttpRequest> HttpRequest = UOcugineBlueprintLibrary::CreateHttpRequest(UOcugineBlueprintLibrary::USERS_OBJECT, "get_policy_info", PostContent);
	HttpRequest->OnProcessRequestComplete().BindStatic(&UOcugineBlueprintLibrary::OcugineGetPolicyInfo_HttpRequestComplete, SuccessCallback, ErrorCallback);
	HttpRequest->ProcessRequest();
}
void UOcugineBlueprintLibrary::OcugineGetPolicyInfo_HttpRequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, FOnGetPolicyInfoComplete SuccessCallback, FOnError ErrorCallback)
{
	if (bSucceeded)
	{ // If request succeeded
		FString ResponseStr = HttpResponse->GetContentAsString(); FOcuginePolicyModel ConvertedResponse; // Declare temp objects
		if (FJsonObjectConverter::JsonObjectStringToUStruct<FOcuginePolicyModel>(ResponseStr, &ConvertedResponse, 0, 0)) // If converted
		{
			if (ConvertedResponse.complete) { SuccessCallback.ExecuteIfBound(ConvertedResponse); } // If complete is true execute callback
			else { ErrorCallback.ExecuteIfBound(TEXT("Ocugine Error"), ConvertedResponse.message); } // If not completed
		}
		else { ErrorCallback.ExecuteIfBound(TEXT("Parse error"), DEFAULT_PARSE_ERROR); } // If convert exception
	}
	else { ErrorCallback.ExecuteIfBound(TEXT("Request error"), DEFAULT_REQUEST_ERROR); } // If request exception
};

#pragma endregion

//===================================================
//  Ocugine Unteal Engine 4 SDK Utils Module
//===================================================
#pragma region Utils

//============================================================
//  @method     CreateHttpRequest()
//  @type       TSharedRef<IHttpRequest>
//  @usage		Create an HTTP request
//  @args       (FString) Object - Application ID
//				(FString) Method - Application Key
//				(FString) Content - Application Grants
//	@return		(IHttpRequest) Request to send
//============================================================
TSharedRef<IHttpRequest> UOcugineBlueprintLibrary::CreateHttpRequest(const FString & Object, const FString & Method, const FString & Content)
{
	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf(TEXT("%s%s/%s/"), *ServerURL, *Object, *Method));

	if (!Content.IsEmpty())
	{
		HttpRequest->SetHeader(TEXT("User-Agent"), TEXT("X-UnrealEngine-Agent"));
		HttpRequest->SetHeader(TEXT("Content-Type"), TEXT("application/x-www-form-urlencoded"));
		HttpRequest->SetHeader(TEXT("Cache-Control"), TEXT("no-store, no-cache, must-revalidate, post-check=0, pre-check=0"));
		HttpRequest->SetVerb(TEXT("POST"));
		HttpRequest->SetContentAsString(Content);
	}
	else
	{
		HttpRequest->SetVerb(TEXT("GET"));
	}
	return HttpRequest;
}

//============================================================
//  @method     GetDataFromFile()
//  @type       FString
//  @usage		Gets text data from file
//  @args       (FString) FileName - Fle name
//	@return		(FString) Data from file
//============================================================
FString UOcugineBlueprintLibrary::GetDataFromFile(FString FileName, bool IsEncoded)
{
	FString directory = FPaths::ConvertRelativePathToFull(FPaths::ProjectDir());
	FString result;
	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();

	if (PlatformFile.DirectoryExists(*directory))
	{
		FString AbsoluteFilePath = directory + "/" + FileName;
		FFileHelper::LoadFileToString(result, *AbsoluteFilePath);
		if(IsEncoded)
			FBase64::Decode(result, result);
	}
	return result;
}

//============================================================
//  @method     SaveDataToFile()
//  @type       void
//  @usage		Saves text data to file
//  @args       (FString) FileName - Fle name
//			    (FString) Data - String for file
//============================================================
void UOcugineBlueprintLibrary::SaveDataToFile(FString FileName, FString Data)
{
	FString directory = FPaths::ConvertRelativePathToFull(FPaths::ProjectDir());
	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();

	if (PlatformFile.DirectoryExists(*directory))
	{
		FString AbsoluteFilePath = directory + "/" + FileName;
		FFileHelper::SaveStringToFile(Data, *AbsoluteFilePath);
	}
}

//============================================================
//  @method     GetGrantsFromConfig()
//  @type       FString
//  @usage		Returns
//============================================================
FString UOcugineBlueprintLibrary::GetGrantsFromConfig()
{
	FOcugineConfigGrantsTypes data = GetDefault<UCustomGameSettings>()->Grants;
	FString result = "";

	if (data.profile) result += "profile%2C";
	if (data.reports) result += "reports%2C";
	if (data.payments) result += "payments%2C";
	if (data.promos) result += "promos%2C";
	if (data.support_tickets) result += "support_tickets%2C";
	if (data.reviews) result += "reviews%2C";
	if (data.apps) result += "apps%2C";
	if (data.leaderboards) result += "leaderboards%2C";
	if (data.messages) result += "messages%2C";
	if (data.achivements) result += "achivements%2C";
	if (data.teams) result += "teams%2C";
	if (data.multiplayer) result += "multiplayer%2C";
	if (data.social) result += "social%2C";
	if (data.cloud_data) result += "cloud_data%2C"; // Do not forget last ,

	FString temp = "";
	if (result == "profile%2Creports%2Cpayments%2Cpromos%2Csupport_tickets%2Creviews%2Capps%2Cleaderboards%2Cmessages%2Cachivements%2Cteams%2Cmultiplayer%2Csocial%2Ccloud_data%2C")
		temp += TEXT("all");
	else {
		result.RemoveAt(result.Len() - 3, 3);
		temp += result;
	}

	return temp;
}

//============================================================
//  @method     GetApplicationLanguageFromConfig()
//  @type       FString
//  @usage		Returns
//============================================================
FString UOcugineBlueprintLibrary::GetApplicationLanguageFromConfig()
{
	switch (GetDefault<UCustomGameSettings>()->Language)
	{
	case (EOcugineConfigLanguageType::OLANGen):
		return "en";
	case (EOcugineConfigLanguageType::OLANGru):
		return "ru";
	default:
		return "en";
	}
}

#pragma endregion