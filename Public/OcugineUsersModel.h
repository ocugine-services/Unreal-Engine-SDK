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
#include "OcugineUsersModel.generated.h"

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