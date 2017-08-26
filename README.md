----

# 使用Demo前，请阅读：


1. 需要自己下载cocos2d-x-3.14.1，并将其内容放入Demo中的cocos2d下。修改cocos2dx源码的一个头文件： 打开cocos2d/cocos/renderer/CCTrianglesCommand.h文件，将TrianglesCommand类中的函数void useMaterial() const;改为virtual void useMaterial() const;
    
2. 联系商务，从 https://pan.baidu.com/s/1mi3K7Io ， 下载SDK并解压。 将解压文件内容，放到Demo中AgoraGamingSDK下。 
    
3. 填入真实 APP Id.

4. 编译. 
----
# Android

## 游戏视频快速入门 (Cocos2d) - Android 
#### 使用 Agora 的 Hello-Cocos2dVideo-Agora 代码示例可以实现以下功能:
- 创建/加入频道
- 视频发言
- 离开频道

### 步骤 1: 准备环境
1. 联系商务[下载]( https://pan.baidu.com/s/1mi3K7Io )最新的SDK 软件包。软件包结构如下:

  ![](https://github.com/AgoraBeck/Cocos2dxResources/blob/master/sdk_list.png)

> 注解:   Hello-Cocos2dVideo-Agora 即为本文需要使用的代码示例。可直接从 Github 下载。

2. 请确保已满足以下环境要求:
• Cocos2d 3.14.1 或更高版本
• Android Studio 2.0 或更高版本
• 两部或多部支持音频功能的 Android 真机(4.0 或更高版本)
• 一个 App ID， 详见 [获取App ID](https://docs.agora.io/cn/game_1.1/user_guide/Component_and_Others/Dynamic_Key_User_Guide.html#get-app-id)。

### 步骤 2: 编译代码示例
	
1. 用 Android Studio 打开项目 proj.android-studio 。
2. 修改 app/src/org/cocos2d/cpp/AGApplication.java 当中的 appId。
3. 连接好真机，点击 Run 按钮编译代码示例。
	
### 步骤 3: 演示游戏语音
演示游戏语音至少需要两部或多部 Android 真机，本文仅以两部手机为例进行演示。

1. 在两部手机上输入相同频道名称。
  
  ![](https://github.com/AgoraBeck/Cocos2dxResources/blob/master/demo_show.png)

2. 点击 Join Channel 即可加入同一频道。
	
  你现在可以在频道内自由发言了！请观察该页面的文字提示消息来确定演示程序的运行状况。


## 集成游戏 (Cocos2d) - Android

### 步骤 1: 准备环境

1. 联系商务[下载](https://pan.baidu.com/s/1mi3K7Io )最新的SDK 软件包。软件包结构如下:
 
 ![](https://github.com/AgoraBeck/Cocos2dxResources/blob/master/sdk_list.png)
 
- include: 头文件。Cocos2d 项目中，用到Agora的视频通信服务的API。
- libs: 库文件, Android仅需使用 Android 文件夹里的 .jar 和 .so 文件。

2. 请确保已满足以下环境要求:
- Android Studio 2.0 或更高版本
- 支持音频功能的 Android 真机(4.0 或更高版本)
- 一个 App ID，详见 [获取App ID](https://docs.agora.io/cn/game_1.1/user_guide/Component_and_Others/Dynamic_Key_User_Guide.html#get-app-id)。

- Cocos2d-x-3.14.1或者更高版本。
###  步骤 2: 新建项目
新建一个 Cocos2d 项目。如有需要，请参考[这里](http://www.cocos2d-x.org/wiki/How_to_Start_A_New_Cocos2D-X_Game) 。 如果已经有了项目，请跳过该步骤。

### 步骤 3: 添加 SDK
1. 在项目根目录下创建一个文件夹，例如: AgoraGamingSDK。

2. 将 SDK的include 和 libs 文件夹拷贝到 AgoraGamingSDK 里。

3. 添加 .jar 文件。将以下语句添加到 proj.android-studio/app/build.gradle 当中 dependencies 处:
  compile fileTree(include: ['*.jar'], dir: '../../AgoraGamingSDK/libs/android')

4. 添加 .jar 文件。将以下语句添加到 proj.android-studio/app/build.gradle 当中 dependencies 处:

- a. 在 proj.android-studio/app/build.gradle 当中 sourceSets.main 处添加以下语句: 

  jniLibs.srcDirs = ["libs", "../../AgoraGamingSDK/libs/Android"]

- 或者通过 Android Studio 图形化界面 Project Structure 也可以完成: 
  ![](https://github.com/AgoraBeck/Cocos2dxResources/blob/master/Android_gradle.png)

- b. 添加 一个 agora-rtc 的 LOCAL_MODULE，然后引用:  如图中红色方框所示
  ![](https://github.com/AgoraBeck/Cocos2dxResources/blob/master/Android_mk.png)

5. 添加 .h 文件。添加以下内容到 LOCAL_C_INCLUDES 后面:
		$(LOCAL_PATH)/../../../AgoraGamingSDK/include
	
	### 步骤 4: 添加权限
	添加必要权限，例如:
	• android.permission.INTERNET
	• android.permission.RECORD_AUDIO
	• android.permission.MODIFY_AUDIO_SETTINGS
	• android.permission.ACCESS_NETWORK_STATE
	• android.permission.BLUETOOTH
	
  ![](https://github.com/AgoraBeck/Cocos2dxResources/blob/master/Android_xml.png)

  
### 步骤 5: 混淆代码（可选项）
当在混淆代码时，请添加以下代码:
	-keep class io.agora.**{*;}
	
### 步骤 6: 调用 API
请根据 agora_cocos2dx.h 中API 实现所需功能。

### 步骤 7： ndk-build 
点击Android-studio下面状态的“terminal”，进入终端。 执行:
 
 cd app/jni;ndk-build；编译c++文件。  
 
其中ndk-build版本为：android-ndk-r14b 


----

# iOS

## 游戏视频快速入门 (Cocos2d) - iOS 
使用 Agora 的 Hello-Cocos2dVideo-Agora 代码示例可以实现以下功能:

- 创建/加入频道
- 自由发言
- 离开频道

### 步骤 1: 准备环境

1. 联系商务[下载](https://pan.baidu.com/s/1mi3K7Io) 最新的SDK 软件包。软件包结构如下:

 ![](https://github.com/AgoraBeck/Cocos2dxResources/blob/master/sdk_list.png)

> 注解:   Hello-Cocos2dVideo-Agora 即为本文需要使用的代码示例。可直接从 Github 下载。

请确保已满足以下环境要求:
- Cocos2d 3.14.1 或更高版本
- Xcode 8.0 或更高版本
- 两部或多部支持音频功能的 iOS 真机(9.0 或更高版本)
- 一个 App ID， 详见[获取App ID](https://docs.agora.io/cn/game_1.1/user_guide/Component_and_Others/Dynamic_Key_User_Guide.html#get-app-id)。

### 步骤 2: 编译代码示例

1. 使用 Xcode 打开项目 proj.ios_mac 进行编译。
2. 修改 ios/AppController.mm 当中的 appId 。
3. 连接好真机，点击 Run 进行编译。

  如在编译过程中遇到任何问题，请参考[游戏语音常见问题](https://docs.agora.io/cn/game_1.1/user_guide/FAQ/game_cn.html) 。

### 步骤 3: 演示游戏语音
演示游戏语音至少需要两部或多部 iOS 真机，本文仅以两部手机为例进行演示。

1. 在两部手机上输入相同频道名称。

  ![](https://github.com/AgoraBeck/Cocos2dxResources/blob/master/demo_show.png)
  
2. 点击 Join Channel 即可加入同一频道。
	
你现在可以在频道内自由发言了！请观察该页面的文字提示消息来确定演示程序的运行状况。
	


## 集成游戏 (Cocos2d) - iOS



### 步骤 1: 准备环境

1. 联系商务[下载](https://pan.baidu.com/s/1mi3K7Io) 最新的SDK 软件包。软件包结构如下:

 ![](https://github.com/AgoraBeck/Cocos2dxResources/blob/master/sdk_list.png)
 
- include: 头文件。Cocos2d 项目中，用到Agora的视频通信服务的API。
- libs: 库文件, 本文仅需使用 iOS 文件夹里的 framework。

2. 请确保已满足以下环境要求:
	
- Xcode 8.0 或更高版本
- 支持音频功能的 iOS 真机(9.0 或更高版本)
- 一个 App ID，详见 [获取App ID](https://docs.agora.io/cn/game_1.1/user_guide/Component_and_Others/Dynamic_Key_User_Guide.html#get-app-id)。
- Cocos2d-x-3.14.1或者更高版本。

### 步骤 2: 新建项目

新建一个 Cocos2d 项目。如有需要，请参考[这里](http://www.cocos2d-x.org/wiki/How_to_Start_A_New_Cocos2D-X_Game) 。 如果已经有了项目，请跳过该步骤。

### 步骤 3: 添加 SDK
1. 在项目根目录下创建一个文件夹，例如: AgoraGamingSDK。
2. 将 include 和 libs 文件夹拷贝到 AgoraGamingSDK 里。
3. 添加 .framework 文件:
		a. 选中当前 Target 。
		b. 选择 Build Phases > Link Binary With Libraries 。
		c. 点击 +，然后 Add Other...:
		d. 选择 AgoraAudioKit.framework 。
		e. 添加以下必须的系统库:
	
	![](https://github.com/AgoraBeck/Cocos2dxResources/blob/master/iOS_framework.png)
 

### 步骤 4: 关闭 bitcode

1. 选中当前 Target 。
2. 选择 Build Settings 。
3. 选择 Enable Bitcode，并将其设置为 No。
  ![](https://github.com/AgoraBeck/Cocos2dxResources/blob/master/iOS_bitcode.png)
 

### 步骤 5: 引用头文件

Objective-C
Cocos2d 项目默认使用 Objective-C 语言，所以只需要引用头文件就可以:

	#include "../AgoraGamingSDK/include/agora_cocos2dx.h"
	
#### Swift
1. 创建桥接文件，取名为: MyAgora-Bridging-Header.h 。
2. 在桥接文件里引用 AMG SDK。
	
	#include "../AgoraGamingSDK/include/agora_cocos2dx.h"
	
3. 将桥接文件设置为 Objective-C Bridging Header:
4. 选择当前 Target 。
5. 选择 Building Settings > Swift Compiler-General，将 Objective-C Bridging Header 设置为 <Target_Name>/MyAgora-Bridging-Header.h 。
  ![](https://github.com/AgoraBeck/Cocos2dxResources/blob/master/iOS_swift.png)

### 步骤 6: 添加权限

添加必要权限，麦克风和摄像头， 例如 :
  ![](https://github.com/AgoraBeck/Cocos2dxResources/blob/master/iOS_info.png)

### 步骤 7: 调用 API

集成完成后，请根据agora_cocos2dx.h调用 API 实现所需功能。




