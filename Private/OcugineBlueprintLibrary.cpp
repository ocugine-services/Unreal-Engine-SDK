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
	const FString PostContent = FString::Printf(TEXT("app_id=%s&app_key=%s&grants=%s"),
		AppID != "" ? *AppID : *GetDefault<UCustomGameSettings>()->AppID,
		AppKey != "" ? *AppKey : *GetDefault<UCustomGameSettings>()->AppKey,
		Grants != "" ? *Grants : *UOcugineBlueprintLibrary::GetGrantsFromConfig()
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
			*AppID,
			*AppKey,
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
		*AppID,
		*AppKey,
		*AccessToken
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
		*AccessToken
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
FString UOcugineBlueprintLibrary::GetDataFromFile(FString FileName)
{
	FString directory = FPaths::ConvertRelativePathToFull(FPaths::ProjectDir());
	FString result;
	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();

	if (PlatformFile.DirectoryExists(*directory))
	{
		FString AbsoluteFilePath = directory + "/" + FileName;
		FFileHelper::LoadFileToString(result, *AbsoluteFilePath);
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

#pragma endregion