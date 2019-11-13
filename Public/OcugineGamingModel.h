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
#include "OcugineGamingModel.generated.h"

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
