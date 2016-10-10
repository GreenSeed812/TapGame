LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
				   ../../Classes/Animation.cpp \
				   ../../Classes/MainScene/ArtifactButton.cpp \
				   ../../Classes/MainScene/ArReset.cpp \
                   ../../Classes/MainScene/HelloWorldScene.cpp \
                   ../../Classes/MainScene/ServantButton.cpp \
                   ../../Classes/MainScene/PlayerButton.cpp \
				   ../../Classes/MainScene/PlayerInfo.cpp \
				   ../../Classes/MainScene/ServantInfo.cpp \
                   ../../Classes/MainScene/ClickLayer.cpp \
				   ../../Classes/MainScene/SkillCD.cpp \
				   ../../Classes/MainScene/Relife.cpp \
				   ../../Classes/Tool/Rand.cpp \
				   ../../Classes/Tool/Rule.cpp \
				   ../../Classes/Tool/Split.cpp \
				   ../../Classes/Tool/SqLite.cpp \
				   ../../Classes/Tool/SpecManager.cpp \
				   ../../Classes/Tool/sqlite3.c \
				   ../../Classes/Tool/TimeTool.cpp \
				   ../../Classes/Tool/Mask.cpp \
				   ../../Classes/Tool/CoinAnimation.cpp \
				   ../../Classes/SaveData/State.cpp \
				   ../../Classes/SaveData/PlayerData.cpp \
				   ../../Classes/SaveData/PlayerButtonData.cpp \
				   ../../Classes/SaveData/ArtifactData.cpp \
				   ../../Classes/SaveData/AchieveData.cpp \
				   ../../Classes/SaveData/ShopData.cpp \
				   ../../Classes/SaveData/MonsterState.cpp \
				   ../../Classes/SaveData/MissionData.cpp \
				   ../../Classes/SaveData/LeaveGold.cpp \
				   ../../Classes/SaveData/DataStatics.cpp \
				   ../../Classes/Ui/bossButton.cpp \
				   ../../Classes/LoadingScene/LoadingScene.cpp \
				   ../../Classes/Ui/AchieveLayer.cpp \
				   ../../Classes/Ui/AchieveItem.cpp \
				   ../../Classes/Ui/ArStarUp.cpp \
				   ../../Classes/Ui/MissionLayer.cpp \
				   ../../Classes/Ui/TaskItem.cpp \
				   ../../Classes/Ui/settingLayer.cpp \
				   ../../Classes/Ui/SignLayer.cpp \
				   ../../Classes/Ui/BgMusic.cpp \
				   ../../Classes/Ui/ExChange.cpp \
				   ../../Classes/Ui/ItemLayer.cpp \
				   ../../Classes/Ui/Statistics.cpp \
				  	  
				   


LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cocos2dx_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END


#ccc3 -> color3b
#lanmuda 【&-》this】
#Split 没有 include string
#tbm->setString(Ruler::getInstance()->showNum(PlayerData::getInstance()->getHpByID(PlayerData::getInstance()->getLevel())));