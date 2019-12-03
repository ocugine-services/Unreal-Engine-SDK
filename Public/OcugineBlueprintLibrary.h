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
// Users delegates
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnGetUsersListComplete, const FOcugineUsersListModel&, UsersListData);
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnFindUserComplete, const FOcugineUsersListModel&, UsersListData);
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnGetUserDataComplete, const FOcugineUserModel&, UserData);
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnGetUserByIDComplete, const FOcugineUserModel&, UserData);
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnGetBanStateComplete, const FOcugineBanStateModel&, BanStateData);
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnGetGroupDataComplete, const FOcugineGroupModel&, GroupData);
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnGetGroupsListComplete, const FOcugineGroupsListModel&, GroupListData);
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnSetGroupComplete, const FOcugineBaseModel&, BaseData);
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnGetAdvancedFieldsComplete, const FOcugineAdvancedFieldsListModel&, AdvancedFieldsListData);
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnSetAdvancedFieldComplete, const FOcugineBaseModel&, BaseData);
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnGetSupportCategoriesComplete, const FOcugineSupportCategoriesListModel&, SupportCategoriesListData);
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnGetSupportTopicsComplete, const FOcugineSupportTopicsListModel&, SupportTopicsListData);
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnGetSupportMessagesComplete, const FOcugineSupportMessagesListModel&, SupportMessagesListData);
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnCreateSupportTopicComplete, const FOcugineBaseModel&, BaseData);
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnUpdateSupportTopicComplete, const FOcugineBaseModel&, BaseData);
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnCloseSupportTopicComplete, const FOcugineBaseModel&, BaseData);
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnSendSupportMessageComplete, const FOcugineBaseModel&, BaseData);
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnGetChatRoomsComplete, const FOcugineChatRoomsListModel&, ChatRoomsListData);
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnGetChatMessagesComplete, const FOcugineChatMessagesListModel&, ChatMessagesListData);
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnSendChatMessageComplete, const FOcugineBaseModel&, BaseData);
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnSendReviewComplete, const FOcugineReviewsListModel&, ReviewsListData);
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnGetReviewsListComplete, const FOcugineReviewsListModel&, ReviewsListData);
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnGetPolicyListComplete, const FOcuginePolicyListModel&, PolicyListData);
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnGetPolicyInfoComplete, const FOcuginePolicyModel&, PolicyData);
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

	/** Users Module **/	
	// GetUsersList
	UFUNCTION(BlueprintCallable, Category = "Ocugine|Users", meta = (AutoCreateRefTerm = "SuccessCallback, ErrorCallback"))
		static void OcugineGetUsersList(const FString & AppID, const FString & AppKey, const int64 Page, const FOnGetUsersListComplete& SuccessCallback, const FOnError& ErrorCallback);
	static void OcugineGetUsersList_HttpRequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, FOnGetUsersListComplete SuccessCallback, FOnError ErrorCallback);
	// FindUser
	UFUNCTION(BlueprintCallable, Category = "Ocugine|Users", meta = (AutoCreateRefTerm = "SuccessCallback, ErrorCallback"))
		static void OcugineFindUser(const FString & AppID, const FString & AppKey, const FString & Search, const int64 Page, const FOnFindUserComplete& SuccessCallback, const FOnError& ErrorCallback);
	static void OcugineFindUser_HttpRequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, FOnFindUserComplete SuccessCallback, FOnError ErrorCallback);
	// GetUserData
	UFUNCTION(BlueprintCallable, Category = "Ocugine|Users", meta = (AutoCreateRefTerm = "SuccessCallback, ErrorCallback"))
		static void OcugineGetUserData(const FString & AppID, const FString & AppKey, const FString & AccessToken, const FOnGetUserDataComplete& SuccessCallback, const FOnError& ErrorCallback);
	static void OcugineGetUserData_HttpRequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, FOnGetUserDataComplete SuccessCallback, FOnError ErrorCallback);
	// GetUserByID
	UFUNCTION(BlueprintCallable, Category = "Ocugine|Users", meta = (AutoCreateRefTerm = "SuccessCallback, ErrorCallback"))
		static void OcugineGetUserByID(const FString & AppID, const FString & AppKey, const int64 ProfileUid, const FOnGetUserByIDComplete& SuccessCallback, const FOnError& ErrorCallback);
	static void OcugineGetUserByID_HttpRequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, FOnGetUserByIDComplete SuccessCallback, FOnError ErrorCallback);
	// GetBanState
	UFUNCTION(BlueprintCallable, Category = "Ocugine|Users", meta = (AutoCreateRefTerm = "SuccessCallback, ErrorCallback"))
		static void OcugineGetBanState(const FString & AppID, const FString & AppKey, const int64 ProfileUid, const FOnGetBanStateComplete& SuccessCallback, const FOnError& ErrorCallback);
	static void OcugineGetBanState_HttpRequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, FOnGetBanStateComplete SuccessCallback, FOnError ErrorCallback);
	// GetGroupData
	UFUNCTION(BlueprintCallable, Category = "Ocugine|Users", meta = (AutoCreateRefTerm = "SuccessCallback, ErrorCallback"))
		static void OcugineGetGroupData(const FString & AppID, const FString & AppKey, const int64 GroupId, const FOnGetGroupDataComplete& SuccessCallback, const FOnError& ErrorCallback);
	static void OcugineGetGroupData_HttpRequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, FOnGetGroupDataComplete SuccessCallback, FOnError ErrorCallback);
	// GetGroupsList
	UFUNCTION(BlueprintCallable, Category = "Ocugine|Users", meta = (AutoCreateRefTerm = "SuccessCallback, ErrorCallback"))
		static void OcugineGetGroupsList(const FString & AppID, const FString & AppKey, const FOnGetGroupsListComplete& SuccessCallback, const FOnError& ErrorCallback);
	static void OcugineGetGroupsList_HttpRequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, FOnGetGroupsListComplete SuccessCallback, FOnError ErrorCallback);
	// SetGroup
	UFUNCTION(BlueprintCallable, Category = "Ocugine|Users", meta = (AutoCreateRefTerm = "SuccessCallback, ErrorCallback"))
		static void OcugineSetGroup(const FString & AppID, const FString & AppKey, const FString & AccessToken, const int64 ProfileUid, const int64 GroupId, const FOnSetGroupComplete& SuccessCallback, const FOnError& ErrorCallback);
	static void OcugineSetGroup_HttpRequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, FOnSetGroupComplete SuccessCallback, FOnError ErrorCallback);
	// GetAdvancedFields
	UFUNCTION(BlueprintCallable, Category = "Ocugine|Users", meta = (AutoCreateRefTerm = "SuccessCallback, ErrorCallback"))
		static void OcugineGetAdvancedFields(const FString & AppID, const FString & AppKey, const int64 Page, const FString & Search, const FOnGetAdvancedFieldsComplete& SuccessCallback, const FOnError& ErrorCallback);
	static void OcugineGetAdvancedFields_HttpRequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, FOnGetAdvancedFieldsComplete SuccessCallback, FOnError ErrorCallback);
	// SetAdvancedField
	UFUNCTION(BlueprintCallable, Category = "Ocugine|Users", meta = (AutoCreateRefTerm = "SuccessCallback, ErrorCallback"))
		static void OcugineSetAdvancedField(const FString & AppID, const FString & AppKey, const FString & AccessToken, const int64 ProfileUid, const int64 FieldId, const FString & Value, const FOnSetAdvancedFieldComplete& SuccessCallback, const FOnError& ErrorCallback);
	static void OcugineSetAdvancedField_HttpRequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, FOnSetAdvancedFieldComplete SuccessCallback, FOnError ErrorCallback);
	// GetSupportCategories
	UFUNCTION(BlueprintCallable, Category = "Ocugine|Users", meta = (AutoCreateRefTerm = "SuccessCallback, ErrorCallback"))
		static void OcugineGetSupportCategories(const FString & AppID, const FString & AppKey, const FOnGetSupportCategoriesComplete& SuccessCallback, const FOnError& ErrorCallback);
	static void OcugineGetSupportCategories_HttpRequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, FOnGetSupportCategoriesComplete SuccessCallback, FOnError ErrorCallback);
	// GetSupportTopics
	UFUNCTION(BlueprintCallable, Category = "Ocugine|Users", meta = (AutoCreateRefTerm = "SuccessCallback, ErrorCallback"))
		static void OcugineGetSupportTopics(const FString & AppID, const FString & AppKey, const int64 CategoryUid, const int64 Page, const FString & Search, const FOnGetSupportTopicsComplete& SuccessCallback, const FOnError& ErrorCallback);
	static void OcugineGetSupportTopics_HttpRequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, FOnGetSupportTopicsComplete SuccessCallback, FOnError ErrorCallback);
	// GetSupportMessages
	UFUNCTION(BlueprintCallable, Category = "Ocugine|Users", meta = (AutoCreateRefTerm = "SuccessCallback, ErrorCallback"))
		static void OcugineGetSupportMessages(const FString & AppID, const FString & AppKey, const int64 TopicUid, const int64 Page, const FString & Search, const FOnGetSupportMessagesComplete& SuccessCallback, const FOnError& ErrorCallback);
	static void OcugineGetSupportMessages_HttpRequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, FOnGetSupportMessagesComplete SuccessCallback, FOnError ErrorCallback);
	// CreateSupportTopic
	UFUNCTION(BlueprintCallable, Category = "Ocugine|Users", meta = (AutoCreateRefTerm = "SuccessCallback, ErrorCallback"))
		static void OcugineCreateSupportTopic(const FString & AppID, const FString & AppKey, const FString & AccessToken, const int64 CategoryUid, const FString & Name, const FString & Body, const FOnCreateSupportTopicComplete& SuccessCallback, const FOnError& ErrorCallback);
	static void OcugineCreateSupportTopic_HttpRequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, FOnCreateSupportTopicComplete SuccessCallback, FOnError ErrorCallback);
	// UpdateSupportTopic
	UFUNCTION(BlueprintCallable, Category = "Ocugine|Users", meta = (AutoCreateRefTerm = "SuccessCallback, ErrorCallback"))
		static void OcugineUpdateSupportTopic(const FString & AppID, const FString & AppKey, const FString & AccessToken, const int64 CategoryUid, const int64 TopicUid, const FString & Name, const FString & Body, const FOnUpdateSupportTopicComplete& SuccessCallback, const FOnError& ErrorCallback);
	static void OcugineUpdateSupportTopic_HttpRequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, FOnUpdateSupportTopicComplete SuccessCallback, FOnError ErrorCallback);
	// CloseSupportTopic
	UFUNCTION(BlueprintCallable, Category = "Ocugine|Users", meta = (AutoCreateRefTerm = "SuccessCallback, ErrorCallback"))
		static void OcugineCloseSupportTopic(const FString & AppID, const FString & AppKey, const FString & AccessToken, const int64 TopicUid, const FOnCloseSupportTopicComplete& SuccessCallback, const FOnError& ErrorCallback);
	static void OcugineCloseSupportTopic_HttpRequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, FOnCloseSupportTopicComplete SuccessCallback, FOnError ErrorCallback);
	// SendSupportMessage
	UFUNCTION(BlueprintCallable, Category = "Ocugine|Users", meta = (AutoCreateRefTerm = "SuccessCallback, ErrorCallback"))
		static void OcugineSendSupportMessage(const FString & AppID, const FString & AppKey, const FString & AccessToken, const int64 TopicUid, const FString & Message, const FOnSendSupportMessageComplete& SuccessCallback, const FOnError& ErrorCallback);
	static void OcugineSendSupportMessage_HttpRequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, FOnSendSupportMessageComplete SuccessCallback, FOnError ErrorCallback);
	// GetChatRooms
	UFUNCTION(BlueprintCallable, Category = "Ocugine|Users", meta = (AutoCreateRefTerm = "SuccessCallback, ErrorCallback"))
		static void OcugineGetChatRooms(const FString & AppID, const FString & AppKey, const FOnGetChatRoomsComplete& SuccessCallback, const FOnError& ErrorCallback);
	static void OcugineGetChatRooms_HttpRequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, FOnGetChatRoomsComplete SuccessCallback, FOnError ErrorCallback);
	// GetChatMessages
	UFUNCTION(BlueprintCallable, Category = "Ocugine|Users", meta = (AutoCreateRefTerm = "SuccessCallback, ErrorCallback"))
		static void OcugineGetChatMessages(const FString & AppID, const FString & AppKey, const int64 RoomId, const FOnGetChatMessagesComplete& SuccessCallback, const FOnError& ErrorCallback);
	static void OcugineGetChatMessages_HttpRequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, FOnGetChatMessagesComplete SuccessCallback, FOnError ErrorCallback);
	// SendChatMessage
	UFUNCTION(BlueprintCallable, Category = "Ocugine|Users", meta = (AutoCreateRefTerm = "SuccessCallback, ErrorCallback"))
		static void OcugineSendChatMessage(const FString & AppID, const FString & AppKey, const FString & AccessToken, const int64 RoomId, const FString & Message, const FOnSendChatMessageComplete& SuccessCallback, const FOnError& ErrorCallback);
	static void OcugineSendChatMessage_HttpRequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, FOnSendChatMessageComplete SuccessCallback, FOnError ErrorCallback);
	// SendReview
	UFUNCTION(BlueprintCallable, Category = "Ocugine|Users", meta = (AutoCreateRefTerm = "SuccessCallback, ErrorCallback"))
		static void OcugineSendReview(const FString & AppID, const FString & AppKey, const FString & AccessToken, const FString & Message, const int64 Stars, const FOnSendReviewComplete& SuccessCallback, const FOnError& ErrorCallback);
	static void OcugineSendReview_HttpRequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, FOnSendReviewComplete SuccessCallback, FOnError ErrorCallback);
	// GetReviewsList
	UFUNCTION(BlueprintCallable, Category = "Ocugine|Users", meta = (AutoCreateRefTerm = "SuccessCallback, ErrorCallback"))
		static void OcugineGetReviewsList(const FString & AppID, const FString & AppKey, const int64 Page, const FString & Search, const FOnGetReviewsListComplete& SuccessCallback, const FOnError& ErrorCallback);
	static void OcugineGetReviewsList_HttpRequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, FOnGetReviewsListComplete SuccessCallback, FOnError ErrorCallback);
	// GetPolicyList
	UFUNCTION(BlueprintCallable, Category = "Ocugine|Users", meta = (AutoCreateRefTerm = "SuccessCallback, ErrorCallback"))
		static void OcugineGetPolicyList(const FString & AppID, const FString & AppKey, const FOnGetPolicyListComplete& SuccessCallback, const FOnError& ErrorCallback);
	static void OcugineGetPolicyList_HttpRequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, FOnGetPolicyListComplete SuccessCallback, FOnError ErrorCallback);
	// GetPolicyInfo
	UFUNCTION(BlueprintCallable, Category = "Ocugine|Users", meta = (AutoCreateRefTerm = "SuccessCallback, ErrorCallback"))
		static void OcugineGetPolicyInfo(const FString & AppID, const FString & AppKey, const int64 Pid, const FOnGetPolicyInfoComplete& SuccessCallback, const FOnError& ErrorCallback);
	static void OcugineGetPolicyInfo_HttpRequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, FOnGetPolicyInfoComplete SuccessCallback, FOnError ErrorCallback);

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