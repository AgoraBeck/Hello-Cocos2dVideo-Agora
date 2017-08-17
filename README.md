1.下载SDK，AgoraGamingSDK中，现在sample的SDK版本是v1_12_FULL，需要自己将cocos2d-x-3.14.1放入sample中,cocos2d下。

修改cocos2dx源码的一个头文件： 打开cocos2d/cocos/renderer/CCTrianglesCommand.h文件，将TrianglesCommand类中的函数void useMaterial() const;改为virtual void useMaterial() const;

2. 填入真实 APP Id.
