#ifndef __HELLOAGORA_SCENE_H__
#define __HELLOAGORA_SCENE_H__

#include "cocos2d.h"

#include "ui/UIEditBox/UIEditBox.h"
#include "../AgoraGamingSDK/include/agora_cocos2dx.h"

USING_NS_CC;
using namespace agora::rtc::cocos2dx;

class TextBox;

class HelloAgora : public agora::rtc::cocos2dx::IAgoraCocos2dxEngineEventHandler
                   ,public cocos2d::Layer
{

private:
    TextBox *mMsgBox = nullptr;
    Label *mMsgLabel = nullptr;
    ui::EditBox *mChannelEditBox = nullptr;
    Sprite* mLocalVideoSprite = nullptr;
    std::map<uint32_t, Sprite*> mRemoteVideoSprites;

public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    virtual void update(float delta);

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloAgora);

private:
    
    //override agora::rtc::cocos2dx::IAgoraCocos2dxEngineEventHandler 
    virtual void onJoinChannelSuccess(const char* channel, uid_t uid, int elapsed) ;
    virtual void onLeaveChannel(const RtcStats& stats) ;
    virtual void onUserJoined(uid_t uid, int elapsed);
    virtual void onUserOffline(uid_t uid, USER_OFFLINE_REASON_TYPE reason);
    virtual void onAudioRouteChanged(AUDIO_ROUTE_TYPE routing) ;
    virtual void onRequestChannelKey() ;
    virtual void onUserMuteVideo(uint32_t uid, bool muted);
    virtual void onUserEnableVideo(uint32_t  uid, bool enabled) ;
    virtual void onRemoteVideoStats(RemoteVideoStats& stats) ;
    virtual void onLocalVideoStats(LocalVideoStats& stats) ;
    virtual void onFirstRemoteVideoFrame(uint32_t uid, int width, int height, int elapsed);
    virtual void onFirstLocalVideoFrame(uint32_t width, int height, int elapsed) ;
    virtual void onFirstRemoteVideoDecoded(uint32_t uid, int width, int height, int elapsed) ;
    virtual void onVideoSizeChanged(uint32_t uid, int width, int height, int rotation) ;
    virtual void onCameraReady() ;
    virtual void onVideoStopped();
    virtual void onJoinChannelClicked();
    virtual void onLeaveChannelClicked();
    virtual void onAudioVolumeIndication(const AudioVolumeInfo* speakers, unsigned int speakerNumber, int totalVolume);

public:
    void updateMsgContent(const std::string& msg);
};

#endif // __HELLOAGORA_SCENE_H__
