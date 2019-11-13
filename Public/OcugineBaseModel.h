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
#include "OcugineBaseModel.generated.h"

//===================================================
//  Ocugine Base Model
//===================================================
#pragma region Base Model
USTRUCT(BlueprintType) struct FOcugineBaseModel
{
	GENERATED_BODY();

	UPROPERTY(EditAnywhere, BlueprintReadOnly) bool complete;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FString message;
};
#pragma endregion

//===================================================
//  Ocugine Enumerators
//===================================================s
#pragma region Enums
// Advanced Field Type
UENUM(BlueprintType) enum EOcugineAdvancedFieldType {
	OAFTTextLine UMETA(DisplayName = "Text Line"),
	OAFTNumber UMETA(DisplayName = "Number"),
	OAFTSelectable UMETA(DisplayName = "Selectable"),
	OAFTMultiselect UMETA(DisplayName = "Multiselect"),
	OAFTTextArea UMETA(DisplayName = "Text Area"),
	OAFTPhone UMETA(DisplayName = "Phone"),
	OAFTEmail UMETA(DisplayName = "Email"),
	OAFTImage UMETA(DisplayName = "Image"),
	OAFTURL UMETA(DisplayName = "URL"),
	OAFTCheckbox UMETA(DisplayName = "Checkbox")
};
UENUM(BlueprintType) enum EOcuginePlatformType {
	OPlTAll UMETA(DisplayName = "All"),
	OPlTAndroid UMETA(DisplayName = "Android"),
	OPlTiOS UMETA(DisplayName = "iOS"),
	OPlTWindowsStandalone UMETA(DisplayName = "Windows (Standalone)"),
	OPlTWindowsUWP UMETA(DisplayName = "Windows (UWP)"),
	OPlTXboxOne UMETA(DisplayName = "Xbox One"),
	OPlTPlaystation4 UMETA(DisplayName = "Playstation 4"),
	OPlTNintendoSwitch UMETA(DisplayName = "Nintendo Switch"),
	OPlTWeb UMETA(DisplayName = "Web"),
	OPlTMacLinux UMETA(DisplayName = "Mac / Linux")
};
UENUM(BlueprintType) enum EOcuginePriorityType {
	OPrTLow UMETA(DisplayName = "Low"),
	OPrTNormal UMETA(DisplayName = "Normal"),
	OPrTHigh UMETA(DisplayName = "High"),
	OPrTVeryHigh UMETA(DisplayName = "Very High")
};
UENUM(BlueprintType) enum EOcugineConfigType {
	OConfText UMETA(DisplayName = "Text"),
	OConfDouble UMETA(DisplayName = "Double"),
	OConfJSON UMETA(DisplayName = "JSON")
};
UENUM(BlueprintType) enum EOcugineOrderType {
	OOrderASC UMETA(DisplayName = "Ascending"),
	OOrderDESC UMETA(DisplayName = "Descending")
};
#pragma endregion

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

//===================================================
//  Ocugine Users Models
//===================================================
#pragma region Users Models

///================= Short models =================///

/* Profile model */
USTRUCT(BlueprintType) struct FOcugineProfileModel
{
	GENERATED_BODY();

	UPROPERTY(EditAnywhere, BlueprintReadOnly) int64 uid;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FString first_name;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FString last_name;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FString avatar;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FString email;
};
/* Advanced Field Model */
USTRUCT(BlueprintType) struct FOcugineAdvancedFieldModel
{
	GENERATED_BODY();

	UPROPERTY(EditAnywhere, BlueprintReadOnly) int64 uid;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FString name;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FString sorting;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) bool hidden;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) TEnumAsByte<EOcugineAdvancedFieldType> type;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int64 project_id;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) bool required;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FString default_value;
};
/* Ban Data Model */
USTRUCT(BlueprintType) struct FOcugineBanStateDataModel
{
	GENERATED_BODY();

	UPROPERTY(EditAnywhere, BlueprintReadOnly) bool ban_state;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FString ban_reason;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int64 ban_escape_time;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int64 ban_escape_days;
};
/* Message Data Model */
USTRUCT(BlueprintType) struct FOcugineMessageDataModel
{
	GENERATED_BODY();

	UPROPERTY(EditAnywhere, BlueprintReadOnly) int64 uid;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int64 profile_uid;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int64 project_id;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int64 room_id;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FString message;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int64 time;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FString date;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FOcugineProfileModel sender;
};

///================= Main models =================///

/**================== PROFILES ===================**/

/* Ban State Model */
USTRUCT(BlueprintType) struct FOcugineBanStateModel : public FOcugineBaseModel { GENERATED_BODY(); UPROPERTY(EditAnywhere, BlueprintReadOnly) FOcugineBanStateDataModel data; };
/* User List Model */
USTRUCT(BlueprintType) struct FOcugineUsersListDataListModel
{
	GENERATED_BODY();

	UPROPERTY(EditAnywhere, BlueprintReadOnly) int64 uid;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FString first_name;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FString last_name;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FString avatar;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FString email;
	// Implement ProfileDataModel[]
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int64 profile_uid;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int64 group_id;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FOcugineBanStateDataModel ban_data;
};
USTRUCT(BlueprintType) struct FOcugineUsersListDataModel { GENERATED_BODY(); UPROPERTY(EditAnywhere, BlueprintReadOnly) TArray<FOcugineUsersListDataListModel> list; };
USTRUCT(BlueprintType) struct FOcugineUsersListModel : public FOcugineBaseModel { GENERATED_BODY(); UPROPERTY(EditAnywhere, BlueprintReadOnly) FOcugineUsersListDataModel data; };
/* User Data Model */
USTRUCT(BlueprintType) struct FOcugineUserDataModel
{
	GENERATED_BODY();

	UPROPERTY(EditAnywhere, BlueprintReadOnly) int64 group_id;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FOcugineProfileModel base_data;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) TArray<FOcugineAdvancedFieldModel> advanced_fields;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FOcugineBanStateDataModel ban_data;
};
USTRUCT(BlueprintType) struct FOcugineUserModel : public FOcugineBaseModel { GENERATED_BODY(); UPROPERTY(EditAnywhere, BlueprintReadOnly) FOcugineUserDataModel data; };

/**================== GROUPS ===================**/

/* Group Data Model */
USTRUCT(BlueprintType) struct FOcugineGroupDataModel
{
	GENERATED_BODY();

	UPROPERTY(EditAnywhere, BlueprintReadOnly) int64 uid;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int64 project_id;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FString group_name;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FString group_desc;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FString time;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) bool can_select;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) bool auto_detect;
};
USTRUCT(BlueprintType) struct FOcugineGroupModel : public FOcugineBaseModel { GENERATED_BODY(); UPROPERTY(EditAnywhere, BlueprintReadOnly) FOcugineGroupDataModel data; };
/* Group List Model */
USTRUCT(BlueprintType) struct FOcugineGroupsListDataModel { GENERATED_BODY(); UPROPERTY(EditAnywhere, BlueprintReadOnly) TArray<FOcugineGroupDataModel> list; };
USTRUCT(BlueprintType) struct FOcugineGroupsListModel : public FOcugineBaseModel { GENERATED_BODY(); UPROPERTY(EditAnywhere, BlueprintReadOnly) FOcugineGroupsListDataModel data; };

/**=============== ADVANCED FIELDS ================**/

/* Advanced Fields List Model */
USTRUCT(BlueprintType) struct FOcugineAdvancedFieldsListDataModel { GENERATED_BODY(); UPROPERTY(EditAnywhere, BlueprintReadOnly) TArray<FOcugineAdvancedFieldModel> list; };
USTRUCT(BlueprintType) struct FOcugineAdvancedFieldsListModel : public FOcugineBaseModel { GENERATED_BODY(); UPROPERTY(EditAnywhere, BlueprintReadOnly) FOcugineAdvancedFieldsListDataModel data; };

/**=================== POLICY ====================**/

/* Policy list model */
USTRUCT(BlueprintType) struct FOcuginePolicyListDataListModel
{
	GENERATED_BODY();

	UPROPERTY(EditAnywhere, BlueprintReadOnly) int64 uid;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FString policy_name;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FString time;
};
USTRUCT(BlueprintType) struct FOcuginePolicyListDataModel { GENERATED_BODY(); UPROPERTY(EditAnywhere, BlueprintReadOnly) TArray<FOcuginePolicyListDataListModel> list; };
USTRUCT(BlueprintType) struct FOcuginePolicyListModel : public FOcugineBaseModel { GENERATED_BODY(); UPROPERTY(EditAnywhere, BlueprintReadOnly) FOcuginePolicyListDataModel data; };

/* Policy model */
USTRUCT(BlueprintType) struct FOcuginePolicyDataModel
{
	GENERATED_BODY();

	UPROPERTY(EditAnywhere, BlueprintReadOnly) int64 uid;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FString policy_name;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FString policy_text;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int64 project_id;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FString time;
};
USTRUCT(BlueprintType) struct FOcuginePolicyModel : public FOcugineBaseModel { GENERATED_BODY(); UPROPERTY(EditAnywhere, BlueprintReadOnly) FOcuginePolicyDataModel data; };

/**================== REVIEWS ====================**/

/* Reviews list model */
USTRUCT(BlueprintType) struct FOcugineReviewsListDataListModel
{
	GENERATED_BODY();

	UPROPERTY(EditAnywhere, BlueprintReadOnly) int64 uid;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int64 project_id;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int64 profile_uid;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FString review;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int64 rate;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int64 time;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FString platform;
};
USTRUCT(BlueprintType) struct FOcugineReviewsListDataModel { GENERATED_BODY(); UPROPERTY(EditAnywhere, BlueprintReadOnly) TArray<FOcugineReviewsListDataListModel> list; };
USTRUCT(BlueprintType) struct FOcugineReviewsListModel : public FOcugineBaseModel { GENERATED_BODY(); UPROPERTY(EditAnywhere, BlueprintReadOnly) FOcugineReviewsListDataModel data; };

/**================= CHAT ROOMS ==================**/

/* Chat Rooms list model */
USTRUCT(BlueprintType) struct FOcugineChatRoomsListDataListModel
{
	GENERATED_BODY();

	UPROPERTY(EditAnywhere, BlueprintReadOnly) int64 uid;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FString name;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FString desc;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int64 project_id;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int64 hidden;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FOcugineMessageDataModel last_msg;
};
USTRUCT(BlueprintType) struct FOcugineChatRoomsListDataModel { GENERATED_BODY(); UPROPERTY(EditAnywhere, BlueprintReadOnly) TArray<FOcugineChatRoomsListDataListModel> list; };
USTRUCT(BlueprintType) struct FOcugineChatRoomsListModel : public FOcugineBaseModel { GENERATED_BODY(); UPROPERTY(EditAnywhere, BlueprintReadOnly) FOcugineChatRoomsListDataModel data; };
/* Chat Messages list model */
USTRUCT(BlueprintType) struct FOcugineChatMessagesListDataModel { GENERATED_BODY(); UPROPERTY(EditAnywhere, BlueprintReadOnly) TArray<FOcugineMessageDataModel> list; };
USTRUCT(BlueprintType) struct FOcugineChatMessagesListModel : public FOcugineBaseModel { GENERATED_BODY(); UPROPERTY(EditAnywhere, BlueprintReadOnly) FOcugineChatMessagesListDataModel data; };

/**=================== SUPPORT ===================**/

/* Support Categories list model */
USTRUCT(BlueprintType) struct FOcugineSupportCategoriesListDataListModel
{
	GENERATED_BODY();

	UPROPERTY(EditAnywhere, BlueprintReadOnly) int64 uid;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int64 project_id;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FString name;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FString desc;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) bool closed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int64 sorting;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int64 time;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int64 topics_num;
};
USTRUCT(BlueprintType) struct FOcugineSupportCategoriesListDataModel { GENERATED_BODY(); UPROPERTY(EditAnywhere, BlueprintReadOnly) TArray<FOcugineSupportCategoriesListDataListModel> list; };
USTRUCT(BlueprintType) struct FOcugineSupportCategoriesListModel : public FOcugineBaseModel { GENERATED_BODY(); UPROPERTY(EditAnywhere, BlueprintReadOnly) FOcugineSupportCategoriesListDataModel data; };
/* Support Topics list model */
USTRUCT(BlueprintType) struct FOcugineSupportTopicsListDataListModel
{
	GENERATED_BODY();

	UPROPERTY(EditAnywhere, BlueprintReadOnly) int64 uid;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int64 profile_uid;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int64 category_id;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int64 project_id;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int64 creation_time;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int64 last_edit_time;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FString title;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) bool is_closed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FString body;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int64 messages;
};
USTRUCT(BlueprintType) struct FOcugineSupportTopicsListDataModel { GENERATED_BODY(); UPROPERTY(EditAnywhere, BlueprintReadOnly) TArray<FOcugineSupportTopicsListDataListModel> list; };
USTRUCT(BlueprintType) struct FOcugineSupportTopicsListModel : public FOcugineBaseModel { GENERATED_BODY(); UPROPERTY(EditAnywhere, BlueprintReadOnly) FOcugineSupportTopicsListDataModel data; };
/* Support Messages list model */
USTRUCT(BlueprintType) struct FOcugineSupportMessagesListDataListModel
{
	GENERATED_BODY();

	UPROPERTY(EditAnywhere, BlueprintReadOnly) int64 uid;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int64 project_id;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int64 category_id;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int64 profile_uid;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int64 topic_id;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int64 time;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FString message;
};
USTRUCT(BlueprintType) struct FOcugineSupportMessagesListDataModel { GENERATED_BODY(); UPROPERTY(EditAnywhere, BlueprintReadOnly) TArray<FOcugineSupportMessagesListDataListModel> list; };
USTRUCT(BlueprintType) struct FOcugineSupportMessagesListModel : public FOcugineBaseModel { GENERATED_BODY(); UPROPERTY(EditAnywhere, BlueprintReadOnly) FOcugineSupportMessagesListDataModel data; };

/* Notification list model */
USTRUCT(BlueprintType) struct FOcugineNotificationDataModel
{
	GENERATED_BODY();

	UPROPERTY(EditAnywhere, BlueprintReadOnly) int64 uid;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int64 project_id;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FString name;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FString content;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) bool for_authenticated;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) TEnumAsByte<EOcuginePlatformType> platform;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int64 user_group;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int64 time;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int64 end_time;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) TEnumAsByte<EOcuginePriorityType> priority;
};
USTRUCT(BlueprintType) struct FOcugineNotificationListDataModel { GENERATED_BODY(); UPROPERTY(EditAnywhere, BlueprintReadOnly) TArray<FOcugineNotificationDataModel> list; };
USTRUCT(BlueprintType) struct FOcugineNotificationListModel : public FOcugineBaseModel { GENERATED_BODY(); UPROPERTY(EditAnywhere, BlueprintReadOnly) FOcugineNotificationListDataModel data; };
/* Notification model */
USTRUCT(BlueprintType) struct FOcugineNotificationModel : public FOcugineBaseModel { GENERATED_BODY(); UPROPERTY(EditAnywhere, BlueprintReadOnly) FOcugineNotificationDataModel data; };

#pragma endregion

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

//===================================================
//  Ocugine Game Services Models
//===================================================
#pragma region Gaming Models

/**================== MISSIONS ===================**/

/* Mission model */
USTRUCT(BlueprintType) struct FOcugineMissionDataModel
{
	GENERATED_BODY();
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int64 uid;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int64 project_id;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FString name;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FString desc;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FString image;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int64 counter;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int64 next_mission;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int64 time;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int64 players;
};
USTRUCT(BlueprintType) struct FOcugineMissionModel : public FOcugineBaseModel { GENERATED_BODY(); UPROPERTY(EditAnywhere, BlueprintReadOnly) FOcugineMissionDataModel data; };

/* Missions list model */
USTRUCT(BlueprintType) struct FOcugineMissionsListDataModel { GENERATED_BODY(); UPROPERTY(EditAnywhere, BlueprintReadOnly) TArray<FOcugineMissionDataModel> list; };
USTRUCT(BlueprintType) struct FOcugineMissionsListModel : public FOcugineBaseModel { GENERATED_BODY(); UPROPERTY(EditAnywhere, BlueprintReadOnly) FOcugineMissionsListDataModel data; };

/* Player Missions list model */
USTRUCT(BlueprintType) struct FOcuginePlayerMissionsListDataListModel
{
	GENERATED_BODY();
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int64 uid;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int64 project_id;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int64 profile_uid;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int64 mission_id;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int64 counter;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int64 completed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int64 time;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FOcugineMissionDataModel mission_data;
};
USTRUCT(BlueprintType) struct FOcuginePlayerMissionsListDataModel { GENERATED_BODY(); UPROPERTY(EditAnywhere, BlueprintReadOnly) TArray<FOcuginePlayerMissionsListDataListModel> list; };
USTRUCT(BlueprintType) struct FOcuginePlayerMissionsListModel : public FOcugineBaseModel { GENERATED_BODY(); UPROPERTY(EditAnywhere, BlueprintReadOnly) FOcuginePlayerMissionsListDataModel data; };

/* Mission Set Scores model */
USTRUCT(BlueprintType) struct FOcugineMissionSetScoresDataModel
{
	GENERATED_BODY();
	UPROPERTY(EditAnywhere, BlueprintReadOnly) bool mission_complete;
};
USTRUCT(BlueprintType) struct FOcugineMissionSetScoresModel : public FOcugineBaseModel { GENERATED_BODY(); UPROPERTY(EditAnywhere, BlueprintReadOnly) FOcugineMissionSetScoresDataModel data; };

/**================ ACHIEVEMENTS =================**/

/* Achievement model */
USTRUCT(BlueprintType) struct FOcugineAchievementDataModel
{
	GENERATED_BODY();
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int64 uid;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int64 project_id;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FString name;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FString desc;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FString image;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int64 time;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int64 players;
};
USTRUCT(BlueprintType) struct FOcugineAchievementModel : public FOcugineBaseModel { GENERATED_BODY(); UPROPERTY(EditAnywhere, BlueprintReadOnly) FOcugineAchievementDataModel data; };

/* Achievement list model */
USTRUCT(BlueprintType) struct FOcugineAchievementsListDataModel { GENERATED_BODY(); UPROPERTY(EditAnywhere, BlueprintReadOnly) TArray<FOcugineAchievementDataModel> list; };
USTRUCT(BlueprintType) struct FOcugineAchievemenstListModel : public FOcugineBaseModel { GENERATED_BODY(); UPROPERTY(EditAnywhere, BlueprintReadOnly) FOcugineAchievementsListDataModel data; };

/* PlayerAchievements list model */
USTRUCT(BlueprintType) struct FOcuginePlayerAchievementsListDataListModel
{
	GENERATED_BODY();
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int64 uid;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int64 project_id;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int64 achiv_id;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int64 profile_uid;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int64 time;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FOcugineAchievementDataModel info;
};
USTRUCT(BlueprintType) struct FOcuginePlayerAchievementsListDataModel { GENERATED_BODY(); UPROPERTY(EditAnywhere, BlueprintReadOnly) TArray<FOcuginePlayerAchievementsListDataListModel> list; };
USTRUCT(BlueprintType) struct FOcuginePlayerAchievementsListModel : public FOcugineBaseModel { GENERATED_BODY(); UPROPERTY(EditAnywhere, BlueprintReadOnly) FOcuginePlayerAchievementsListDataModel data; };

/**================ LEADERBOARDS =================**/

/* Leaderboard model */
USTRUCT(BlueprintType) struct FOcugineLeaderboardDataModel
{
	GENERATED_BODY();
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int64 uid;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int64 project_id;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FString name;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FString desc;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FString image;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) TEnumAsByte<EOcugineOrderType> ordering;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int64 time;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FString players;
};
USTRUCT(BlueprintType) struct FOcugineLeaderboardModel : public FOcugineBaseModel { GENERATED_BODY(); UPROPERTY(EditAnywhere, BlueprintReadOnly) FOcugineLeaderboardDataModel data; };

/* Leaderboards list model */
USTRUCT(BlueprintType) struct FOcugineLeaderboardsListDataModel { GENERATED_BODY(); UPROPERTY(EditAnywhere, BlueprintReadOnly) TArray<FOcugineLeaderboardDataModel> list; };
USTRUCT(BlueprintType) struct FOcugineLeaderboardsListModel : public FOcugineBaseModel { GENERATED_BODY(); UPROPERTY(EditAnywhere, BlueprintReadOnly) FOcugineLeaderboardsListDataModel data; };

/* Leaderboard Top model */
USTRUCT(BlueprintType) struct FOcugineLeaderboardTopDataListModel
{
	GENERATED_BODY();
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int64 uid;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int64 project_id;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int64 profile_id;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int64 scores;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int64 board_id;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int64 time;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FOcugineProfileModel profile;
};
USTRUCT(BlueprintType) struct FOcugineLeaderboardTopDataModel { GENERATED_BODY(); UPROPERTY(EditAnywhere, BlueprintReadOnly) TArray<FOcugineLeaderboardTopDataListModel> list; };
USTRUCT(BlueprintType) struct FOcugineLeaderboardTopModel : public FOcugineBaseModel { GENERATED_BODY(); UPROPERTY(EditAnywhere, BlueprintReadOnly) FOcugineLeaderboardTopDataModel data; };

/* Leaderboard Player Scores model */
USTRUCT(BlueprintType) struct FOcugineLeaderboardPlayerScoresDataModel
{
	GENERATED_BODY();
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int64 uid;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int64 project_id;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int64 profile_id;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int64 scores;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int64 board_id;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int64 time;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FOcugineProfileModel profile;
};
USTRUCT(BlueprintType) struct FOcugineLeaderboardPlayerScoresModel : public FOcugineBaseModel { GENERATED_BODY(); UPROPERTY(EditAnywhere, BlueprintReadOnly) FOcugineLeaderboardPlayerScoresDataModel data; };


#pragma endregion

//===================================================
//  Ocugine Localization Models
//===================================================
#pragma region Localization Models

/* Language model */
USTRUCT(BlueprintType) struct FOcugineLanguageDataModel
{
	GENERATED_BODY();
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FString uid;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FString code;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FString name;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FString time;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FString project_id;
};
USTRUCT(BlueprintType) struct FOcugineLanguageModel : public FOcugineBaseModel { GENERATED_BODY(); UPROPERTY(EditAnywhere, BlueprintReadOnly) FOcugineLanguageDataModel data; };
/* Language list model */
USTRUCT(BlueprintType) struct FOcugineLanguageListDataModel { GENERATED_BODY(); UPROPERTY(EditAnywhere, BlueprintReadOnly) TArray<FOcugineLanguageDataModel> list; };
USTRUCT(BlueprintType) struct FOcugineLanguageListModel : public FOcugineBaseModel { GENERATED_BODY(); UPROPERTY(EditAnywhere, BlueprintReadOnly) FOcugineLanguageListDataModel data; };

/* Locale model */
USTRUCT(BlueprintType) struct FOcugineLocaleDataModel
{
	GENERATED_BODY();
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FString uid;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FString code;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FString language;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FString value;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FString project_id;
};
USTRUCT(BlueprintType) struct FOcugineLocaleModel : public FOcugineBaseModel { GENERATED_BODY(); UPROPERTY(EditAnywhere, BlueprintReadOnly) FOcugineLocaleDataModel data; };

/* Locale list model */
USTRUCT(BlueprintType) struct FOcugineLocaleListDataModel 
{ 
	GENERATED_BODY();
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FString lang_name;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) TArray<FOcugineLocaleDataModel> list; 
};
USTRUCT(BlueprintType) struct FOcugineLocaleListModel : public FOcugineBaseModel { GENERATED_BODY(); UPROPERTY(EditAnywhere, BlueprintReadOnly) FOcugineLocaleListDataModel data; };

#pragma endregion

//===================================================
//  Ocugine Reports Models
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