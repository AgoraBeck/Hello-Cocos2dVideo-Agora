#include "ui/CocosGUI.h"

#include "HelloAgoraScene.h"
#include "SimpleAudioEngine.h"

#include "TextBox/TextBox.h"

#include "agora_cocos2dx.h"


USING_NS_CC;

#define DIS_SPRITE_W 90
#define DIS_SPRITE_H 90

using namespace agora::rtc::cocos2dx;

Scene* HelloAgora::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = HelloAgora::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloAgora::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloAgora::menuCloseCallback, this));

    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2 ,
                                origin.y + closeItem->getContentSize().height / 2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // create and initialize a label

    auto label = Label::createWithTTF(AgoraRtcEngineForGaming_getInstance()->getVersion(NULL), "fonts/Marker Felt.ttf", 24);

    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width / 2,
                            origin.y + visibleSize.height - label->getContentSize().height));
    // add the label as a child to this layer
    this->addChild(label, 1);
    
    int leftPadding = 10;

    mChannelEditBox = ui::EditBox::create(Size(120, 30), "TextBox.png");
    //mChannelEditBox->setPlaceHolder("Enter Chan...");
    mChannelEditBox->setText("666");
    mChannelEditBox->setPosition(Vec2(origin.x + leftPadding + mChannelEditBox->getContentSize().width / 2, origin.y + visibleSize.height - 1.5 * mChannelEditBox->getContentSize().height));

    this->addChild(mChannelEditBox, 0);
    
    mMsgLabel = Label::create();
    mMsgLabel->setString("11111");
    mMsgLabel->setAnchorPoint(cocos2d::Vec2(0, 1));

    // position the label on the center of the screen
    mMsgLabel->setPosition(Vec2(mChannelEditBox->getPosition().x + mChannelEditBox->getContentSize().width - 40,
                            origin.y + visibleSize.height - label->getContentSize().height -10));


    this->addChild(mMsgLabel, 1);

    auto joinButton = ui::Button::create("Button.png", "ButtonPressed.png", "ButtonPressed.png");
    joinButton->setTitleText("Join Channel");
    joinButton->setPosition(Vec2(origin.x + leftPadding + joinButton->getContentSize().width / 2, origin.y + visibleSize.height - 1 * joinButton->getContentSize().height - 2 * mChannelEditBox->getContentSize().height));

    joinButton->addTouchEventListener([&](cocos2d::Ref* sender, ui::Widget::TouchEventType type) {
        switch (type)
        {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:
                onJoinChannelClicked();
                break;
            default:
                break;
        }
    });

    this->addChild(joinButton, 0);

    auto leaveButton = ui::Button::create("Button.png", "ButtonPressed.png", "ButtonPressed.png");
    leaveButton->setTitleText("Leave Channel");
    leaveButton->setPosition(Vec2(origin.x + leftPadding + leaveButton->getContentSize().width / 2, origin.y + visibleSize.height - 2 * leaveButton->getContentSize().height - 2 * mChannelEditBox->getContentSize().height));

    leaveButton->addTouchEventListener([&](cocos2d::Ref* sender, ui::Widget::TouchEventType type) {
        switch (type)
        {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:
                onLeaveChannelClicked();
                break;
            default:
                break;
        }
    });

    this->addChild(leaveButton, 0);

    AgoraRtcEngineForGaming_getInstance()->setEventHandler((this));
    AgoraRtcEngineForGaming_getInstance()->setLogFile(("/sdcard/cocos2d-log.txt"));

    scheduleUpdate();

    return true;
}

void HelloAgora::update(float delta)
{
    AgoraRtcEngineForGaming_getInstance()->poll();
}

void HelloAgora::updateMsgContent(const std::string& msg)
{
    mMsgLabel->setString(msg);
}

void HelloAgora::onLeaveChannelClicked()
{
    CCLOG("[General C++]:onLeaveChannelClicked ");
    AgoraRtcEngineForGaming_getInstance()->stopPreview();
    AgoraRtcEngineForGaming_getInstance()->leaveChannel();
    auto rtcEngine = AgoraRtcEngineForGaming_getInstance();

    // Release video sprites
    if (mLocalVideoSprite != NULL) {
        rtcEngine->setupLocalVideoSprite(NULL);
        this->removeChild(mLocalVideoSprite);
        mLocalVideoSprite->release();
        mLocalVideoSprite = NULL;
    }
    
    std::map<uint32_t, Sprite*>::iterator it = this->mRemoteVideoSprites.begin();
    for (; it != mRemoteVideoSprites.end(); ++it) {
        rtcEngine->setupRemoteVideoSprite(NULL, it->first);
        this->removeChild(it->second);
        it->second->release();
    }
    mRemoteVideoSprites.clear();
}

void HelloAgora::onJoinChannelClicked()
{
    if (mChannelEditBox == nullptr || ::strlen(mChannelEditBox->getText()) == 0) {
        return;
    }
    CCLOG("[General C++]:onJoinChannelClicked ");

    auto rtcEngine = AgoraRtcEngineForGaming_getInstance();
    rtcEngine->setChannelProfile(CHANNEL_PROFILE_GAME_FREE_MODE);
    rtcEngine->enableVideo(true);
    //rtcEngine->setVideoProfile(agora::rtc::cocos2dx::VIDEOPROFILE_DEFAULT, false);
    rtcEngine->setVideoProfile(agora::rtc::cocos2dx::VIDEOPROFILE_360P_6, false);
     //rtcEngine->setVideoProfile(agora::rtc::cocos2dx::VIDEOPROFILE_480P_6, false);
    rtcEngine->joinChannel(mChannelEditBox->getText(), "Cocos2d", 0);
}

void HelloAgora::menuCloseCallback(Ref* pSender)
{
    onLeaveChannelClicked();

    // Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();
    

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif

    /*To navigate back to native iOS screen(if present) without quitting the application, do not use Director::getInstance()->end() and exit(0) as given above, instead trigger a custom event created in RootViewController.mm as below*/

    // EventCustom customEndEvent("game_scene_close_event");
    // _eventDispatcher->dispatchEvent(&customEndEvent);
}


void HelloAgora::onJoinChannelSuccess(const char* channel, uid_t uid, int elapsed)
{
    std::stringstream rawMsg;
    rawMsg << "onJoinChannelSuccess " << channel << " " << uid << " " << elapsed;
    CCLOG("[General C++]:onJoinChannelSuccess %s, %d, %d", channel, uid, elapsed);
    std::string info = rawMsg.str();
    Director::getInstance()->getScheduler()->performFunctionInCocosThread([&, this, info] {
        this->updateMsgContent(info);
        auto rtcEngine = AgoraRtcEngineForGaming_getInstance();
        if(this->mLocalVideoSprite == NULL) {
            Sprite * sprite = rtcEngine->createSprite();
            sprite->setContentSize(Size(DIS_SPRITE_W, DIS_SPRITE_H));
            auto visibleSize = Director::getInstance()->getVisibleSize();
            Vec2 origin = Director::getInstance()->getVisibleOrigin();
            sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
            this->addChild(sprite);
            rtcEngine->setupLocalVideoSprite(sprite);
            sprite->retain();
            this->mLocalVideoSprite = sprite;
        } else {
            rtcEngine->setupLocalVideoSprite(this->mLocalVideoSprite);
            this->addChild(this->mLocalVideoSprite);
        }
    
    });
}

void HelloAgora::onLeaveChannel(const RtcStats& stats) {
    CCLOG("[General C++]:onLeaveChannel %d, %d, %d", stats.totalDuration, stats.txBytes, stats.rxBytes);
    std::stringstream rawMsg;
    rawMsg << "onLeaveChannel " << stats.totalDuration << " " << stats.txBytes << " " << stats.rxBytes;
    std::string info = rawMsg.str();
    Director::getInstance()->getScheduler()->performFunctionInCocosThread([&, this, info] {
        this->updateMsgContent(info);
    });
}

void HelloAgora::onUserJoined(uid_t uid, int elapsed) {
    CCLOG("[General C++]:onUserJoined uid: %d", uid);
}

void HelloAgora::onUserOffline(uid_t uid, USER_OFFLINE_REASON_TYPE reason) {
    onUserEnableVideo(uid, false);
    CCLOG("[General C++]:onUserOffline uid: %d", uid);
    
}

void HelloAgora::onAudioRouteChanged(AUDIO_ROUTE_TYPE routing) {
    
    CCLOG("[General C++]:onAudioRouteChanged %d", routing);
}

void HelloAgora::onRequestChannelKey() {
    CCLOG("[General C++]:onRequestChannelKey");
}

void HelloAgora::onUserMuteVideo(uint32_t uid, bool muted) {
    CCLOG("[General C++]:onUserMuteVideo uid:%d mute:%d", uid, muted);
    Director::getInstance()->getScheduler()->performFunctionInCocosThread([&, this, uid, muted] {
        std::map<uint32_t, Sprite*>::iterator it = this->mRemoteVideoSprites.find(uid);
        if (it != this->mRemoteVideoSprites.end()) {
            if(muted) {
                this->removeChild(it->second);
            }else {
                this->addChild(it->second);
            }
        }
        
    });
}

void HelloAgora::onUserEnableVideo(uint32_t  uid, bool enabled) {
    CCLOG("[General C++]:onUserEnableVideo uid:%d enable:%d", uid, enabled);
    Director::getInstance()->getScheduler()->performFunctionInCocosThread([&, this, uid, enabled] {
        std::map<uint32_t, Sprite*>::iterator it = this->mRemoteVideoSprites.find(uid);
        if (it != this->mRemoteVideoSprites.end()) {
            if(!enabled) {
                this->removeChild(it->second);
                auto rtcEngine = AgoraRtcEngineForGaming_getInstance();
                rtcEngine->setupRemoteVideoSprite(NULL, uid);
                it->second->release();
                this->mRemoteVideoSprites.erase(it);
            }
        }
    });
}

void HelloAgora::onRemoteVideoStats(RemoteVideoStats& stats) {
    CCLOG("[General C++]:onRemoteVideoStats uid:%d bitrate:%d framerate:%d", stats.uid , stats.receivedBitrate, stats.receivedFrameRate);
}

void HelloAgora::onLocalVideoStats(LocalVideoStats& stats) {
    CCLOG("[General C++]:onLocalVideoStats bitrate:%d framerate:%d", stats.sentBitrate, stats.sentFrameRate);
}

void HelloAgora::onFirstRemoteVideoFrame(uint32_t uid, int width, int height, int elapsed) {
    CCLOG("[General C++]:onFirstRemoteVideoFrame uid:%d width:%d height:%d", uid, width, height);
}

void HelloAgora::onFirstLocalVideoFrame(uint32_t width, int height, int elapsed) {
    CCLOG("[General C++]:onFirstLocalVideoFram width:%d height:%d", width, height);
}

void HelloAgora::onFirstRemoteVideoDecoded(uint32_t uid, int width, int height, int elapsed)  {
    CCLOG("[General C++]:onFirstRemoteVideoDecoded uid:%d, width:%d height:%d", uid, width, height);
    Director::getInstance()->getScheduler()->performFunctionInCocosThread([&, this, uid] {
        std::map<uint32_t, Sprite*>::iterator it = this->mRemoteVideoSprites.find(uid);
        if (it == this->mRemoteVideoSprites.end()) {
            auto rtcEngine = AgoraRtcEngineForGaming_getInstance();
            Sprite * sprite = rtcEngine->createSprite();
            auto visibleSize = Director::getInstance()->getVisibleSize();
            Vec2 origin = Director::getInstance()->getVisibleOrigin();
            sprite->setContentSize(Size(DIS_SPRITE_W, DIS_SPRITE_H));
            sprite->setPosition(Vec2(visibleSize.width/2 + origin.x + DIS_SPRITE_W + 10, visibleSize.height/2 + origin.y));
            this->addChild(sprite);
            sprite->retain();
            this->mRemoteVideoSprites.insert(std::make_pair(uid, sprite));
            rtcEngine->setupRemoteVideoSprite(sprite, uid);
            
        }
    });
}

void HelloAgora::onVideoSizeChanged(uint32_t uid, int width, int height, int rotation) {
    
}

void HelloAgora::onCameraReady() {
    
}

void HelloAgora::onVideoStopped(){
    CCLOG("[General C++]:onVideoStopped");
    Director::getInstance()->getScheduler()->performFunctionInCocosThread([&, this] {
        if (this->mLocalVideoSprite != NULL) {
            CCLOG("[General C++]:onVideoStopped : remove LocalVideo");
            this->removeChild(this->mLocalVideoSprite);
            auto rtcEngine = AgoraRtcEngineForGaming_getInstance();
            rtcEngine->setupLocalVideoSprite(NULL);
        }
    });
}
