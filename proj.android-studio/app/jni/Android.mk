LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := agora-cocos2dx
LOCAL_SRC_FILES := ../../../AgoraGamingSDK/libs/android/$(TARGET_ARCH_ABI)/libagora-cocos2dx.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := agora-rtc
LOCAL_SRC_FILES := ../../../AgoraGamingSDK/libs/android/$(TARGET_ARCH_ABI)/libagora-rtc-sdk-jni.so
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := apm-plugin-agora-cocos2dx
LOCAL_SRC_FILES := ../../../AgoraGamingSDK/libs/android/$(TARGET_ARCH_ABI)/libapm-plugin-agora-cocos2dx.so
include $(PREBUILT_SHARED_LIBRARY)

$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/cocos)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/cocos/audio/include)

LOCAL_MODULE := MyGame_shared

LOCAL_MODULE_FILENAME := libMyGame

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../../Classes/TextBox/TextBox.cpp \
                   ../../../Classes/AppDelegate.cpp \
                   ../../../Classes/HelloAgoraScene.cpp



LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../Classes \
                    $(LOCAL_PATH)/../../../AgoraGamingSDK/include

LOCAL_STATIC_LIBRARIES := cocos2dx_static agora-cocos2dx

LOCAL_SHARED_LIBRARIES := agora-rtc apm-plugin-agora-cocos2dx


include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)

