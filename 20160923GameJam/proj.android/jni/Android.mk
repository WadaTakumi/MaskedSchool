LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/HelloWorldScene.cpp \
                   ../../Classes/BackGround.cpp \
                   ../../Classes/BackGround2.cpp \
                   ../../Classes/BackGround3.cpp \
                   ../../Classes/BackgroundLayer.cpp \
                   ../../Classes/BaseMask.cpp \
                   ../../Classes/DebugDrawNode.cpp \
                   ../../Classes/Enemy.cpp \
                   ../../Classes/EnemyData.cpp \
                   ../../Classes/EventListenerGesture.cpp \
                   ../../Classes/GLES-Render.cpp \
                   ../../Classes/HelloWorldScene.cpp \
                   ../../Classes/main.cpp \
                   ../../Classes/MainScene.cpp \
                   ../../Classes/MaskOfBullet.cpp \
                   ../../Classes/MaskOfFly.cpp \
                   ../../Classes/MaskOfScreenToSpeedUp.cpp \
                   ../../Classes/MaskOfSpeadUp.cpp \
                   ../../Classes/MaskPower.cpp \
                   ../../Classes/MenuScreenScene.cpp \
                   ../../Classes/Player.cpp \
                   ../../Classes/Player.cpp            
                   
                   

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
